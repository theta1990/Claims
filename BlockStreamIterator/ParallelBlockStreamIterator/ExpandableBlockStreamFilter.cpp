/*
 * ExpandableBlockStreamFilter.cpp
 *
 *  Created on: Aug 28, 2013
 *      Author: wangli
 */

#include "ExpandableBlockStreamFilter.h"

ExpandableBlockStreamFilter::ExpandableBlockStreamFilter(State state)
:state_(state),open_finished_(false){
	sem_open_.set_value(1);

}

ExpandableBlockStreamFilter::ExpandableBlockStreamFilter()
:open_finished_(false){
	sem_open_.set_value(1);
}

ExpandableBlockStreamFilter::~ExpandableBlockStreamFilter() {
	// TODO Auto-generated destructor stub
}

ExpandableBlockStreamFilter::State::State(Schema* schema, BlockStreamIteratorBase* child,
		std::vector<FilterIterator::AttributeComparator> comparator_list
		,unsigned block_size)
:schema_(schema),child_(child),comparator_list_(comparator_list),block_size_(block_size){

}


bool ExpandableBlockStreamFilter::open(const PartitionOffset& part_off){

	AtomicPushFreeBlockStream(BlockStreamBase::createBlock(state_.schema_,state_.block_size_));
	printf("Free block stream list added!\n");
	if(sem_open_.try_wait()){

		open_finished_=true;
		return state_.child_->open(part_off);
	}
	else
	{
		while(!open_finished_){
			usleep(1);
		}
		return state_.child_->open(part_off);
	}
}



bool ExpandableBlockStreamFilter::next(BlockStreamBase* block){

	remaining_block rb;
	void* tuple_from_child;
	void* tuple_in_block;
	bool pass_filter;
	if(atomicPopRemainingBlock(rb)){
		while((tuple_from_child=rb.iterator->currentTuple())>0){
			pass_filter=true;
			for(unsigned i=0;i<state_.comparator_list_.size();i++){

//				state_.comparator_list_[0].in

//				if(!state_.comparator_list_[i].filter(tuple_from_child)){
				if(!state_.comparator_list_[i].filter(state_.schema_->getColumnAddess(state_.comparator_list_[i].get_index(),tuple_from_child))){
					pass_filter=false;
					break;
				}
			}
			if(pass_filter){
				const unsigned bytes=state_.schema_->getTupleActualSize(tuple_from_child);
				if((tuple_in_block=block->allocateTuple(bytes))>0){
					/* the block has space to hold this tuple*/
					state_.schema_->copyTuple(tuple_from_child,tuple_in_block);
					rb.iterator->increase_cur_();
				}
				else{
					/* the block is full, before we return, we pop the remaining block.*/
					atomicPushRemainingBlock(rb);
					return true;
				}
			}
			else{
				rb.iterator->increase_cur_();
			}
		}
		AtomicPushFreeBlockStream(rb.block);

	}

	/* When the program arrivals here, it means that there is no remaining block or the remaining block
	 * is exhausted, so we read a new block from the child.
	 */

//	BlockStreamBase* block_for_asking=BlockStreamBase::createBlock(state_.schema_,state_.block_size_);
	BlockStreamBase* block_for_asking=AtomicPopFreeBlockStream();
	block_for_asking->setEmpty();
	while(state_.child_->next(block_for_asking)){
		BlockStreamBase::BlockStreamTraverseIterator* traverse_iterator=block_for_asking->createIterator();
		while((tuple_from_child=traverse_iterator->currentTuple())>0){
			pass_filter=true;
			for(unsigned i=0;i<state_.comparator_list_.size();i++){
				if(!state_.comparator_list_[i].filter(state_.schema_->getColumnAddess(state_.comparator_list_[i].get_index(),tuple_from_child))){
					pass_filter=false;
					break;
				}
			}
			if(pass_filter){
				const unsigned bytes=state_.schema_->getTupleActualSize(tuple_from_child);
				if((tuple_in_block=block->allocateTuple(bytes))>0){
					/* the block has space to hold this tuple*/
					state_.schema_->copyTuple(tuple_from_child,tuple_in_block);
					traverse_iterator->increase_cur_();
				}
				else{
					/* the block is full, before we return, we pop the remaining block.*/
					atomicPushRemainingBlock(remaining_block(block_for_asking,traverse_iterator));
					return true;
				}
			}
			else{
				traverse_iterator->increase_cur_();
			}

		}
		/* the block_for_asking is exhausted, but the block is not full*/
		traverse_iterator->~BlockStreamTraverseIterator();
		block_for_asking->setEmpty();
	}
	/* the child iterator is exhausted, but the block is not full.*/
//	block_for_asking->~BlockStreamBase();
	AtomicPushFreeBlockStream(block_for_asking);
	if(!block->Empty())
		return true;
	else
	return false;
}

bool ExpandableBlockStreamFilter::close(){
	sem_open_.post();
	open_finished_=false;
	free_block_stream_list_.clear();
	state_.child_->close();
	return true;
}
void ExpandableBlockStreamFilter::print(){
	printf("Filter\n");
//	for(unsigned i=0;i<state_.comparator_list_.size();i++){
//		state_.comparator_list_[i].pair.first.
//	}
	printf("---------------\n");
	state_.child_->print();
}
bool ExpandableBlockStreamFilter::atomicPopRemainingBlock(remaining_block & rb){
	lock_.acquire();

	if(remaining_block_list_.size()>0){
		rb=remaining_block_list_.front();
		remaining_block_list_.pop_front();

		lock_.release();

		return true;
	}
	else{

		lock_.release();

		return false;
	}
}

void ExpandableBlockStreamFilter::atomicPushRemainingBlock(remaining_block rb){
	lock_.acquire();
	remaining_block_list_.push_back(rb);
	lock_.release();
}

BlockStreamBase* ExpandableBlockStreamFilter::AtomicPopFreeBlockStream(){
	assert(!free_block_stream_list_.empty());
	lock_.acquire();
	BlockStreamBase *block=free_block_stream_list_.front();
	free_block_stream_list_.pop_front();
	lock_.release();
	return block;
}
void ExpandableBlockStreamFilter::AtomicPushFreeBlockStream(BlockStreamBase* block){
	lock_.acquire();
	free_block_stream_list_.push_back(block);
	lock_.release();
}
