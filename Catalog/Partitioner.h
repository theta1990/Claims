/*
 * Partitioner.h
 *
 *  Created on: 2013-10-14
 *      Author: wangli
 */

#ifndef PARTITIONER_H_
#define PARTITIONER_H_
#include <vector>
#include <string>
#include <map>
#include "../hashmap.hpp"
#include "Attribute.h"
#include "../hash.h"

#include "Partitioner.h"
#include "../Resource/NodeTracker.h"
#include "../ids.h"
/**Partitioner describes how the data is partitioned and what nodes are
 * involved in the partition. *
 */
using namespace std;
//typedef unsigned TableID;
//typedef struct ProjectionID{
//	TableID table_id;
//	size_t local_projection_id;
//	bool operator==(const ProjectionID& r)const{
//		return table_id==r.table_id&&local_projection_id==r.local_projection_id;
//	}
//} ;

typedef unsigned BlockID;
//typedef struct PartitionID{
//	ProjectionID projection_id;
//	unsigned partition_key;
//	bool operator<(const PartitionID& r)const{
//		return projection_id<r.projection_id||partition_key<r.partition_key;
//	}
//};
typedef unsigned PartitionOffset;


typedef struct BlockInfo{
	BlockID block_id;
	int tuple_count;
};
enum binding_mode{OneToOne,OneToMany};
// class StoragePartitoinInfo: public PartitionInfo
class PartitionInfo{
public:

	friend class Partitioner;
	explicit PartitionInfo(PartitionID partition_id):partition_id_(partition_id),number_of_blocks(-1){};
	explicit PartitionInfo(PartitionID partition_id,string file_name)
	:partition_id_(partition_id),hdfs_file_name(file_name),number_of_blocks(0){}

	explicit PartitionInfo(PartitionID partition_id,string file_name,int number_of_blocks)
	:partition_id_(partition_id),hdfs_file_name(file_name),number_of_blocks(number_of_blocks){}

	virtual binding_mode get_mode()const=0;
	virtual void add_one_block()=0;//p
	virtual void add_mutiple_block(unsigned number_of_new_blocks)=0;//p
	virtual bool bind_one_block(BlockID blockid,NodeID target)=0;//p
	virtual bool bind_all_blocks(NodeID target)=0;//p
	virtual void unbind_all_blocks()=0;//p
	virtual bool is_all_blocks_bound()=0;//p
	virtual bool is_colocated(const PartitionInfo &)const=0;
	int get_number_of_blocks()const{	return number_of_blocks;}//p
	virtual NodeID get_location() const=0;
protected:
	string hdfs_file_name;//p
	int number_of_blocks;//p
	PartitionID partition_id_;

};

class OneToOnePartitionInfo:public PartitionInfo{
public:
	OneToOnePartitionInfo(PartitionID pid):PartitionInfo(pid),binding_node_id_(-1){};
	OneToOnePartitionInfo(PartitionID pid,string file_name):PartitionInfo(pid,file_name),binding_node_id_(-1){};
	OneToOnePartitionInfo(PartitionID pid,string file_name,unsigned number_of_blocks):PartitionInfo(pid,file_name,number_of_blocks),binding_node_id_(-1){};
	binding_mode get_mode()const{
		return OneToOne;
	}
	void add_one_block(){
		number_of_blocks++;
	}
	void add_mutiple_block(unsigned number_of_new_blocks){
		number_of_blocks+=number_of_new_blocks;
	}
	bool bind_one_block(BlockID blockid,NodeID target){
		assert(target>=0);
		if(binding_node_id_==-1){
			binding_node_id_=target;
			return true;
		}
		else{
			return target==binding_node_id_;
		}
	}
	bool bind_all_blocks(NodeID target){
		assert(target>=0);
		if(binding_node_id_==-1){
			/*the partition has not been bound to any node*/
			binding_node_id_=target;
			return true;
		}
		else{
			/* the partition has been bound to a node, return true if the target is the same as the original NodeID*/
			return target==binding_node_id_;
		}
	}
	bool is_all_blocks_bound(){
		return binding_node_id_>=0;
	}
	void unbind_all_blocks(){
		binding_node_id_=-1;
	}
	bool is_colocated(const PartitionInfo &)const;
	NodeID get_location() const{return binding_node_id_;}
	virtual ~OneToOnePartitionInfo(){};
private:
	NodeID binding_node_id_;
};

class OneToManyPartitionInfo:public PartitionInfo{
public:
	OneToManyPartitionInfo(PartitionID pid,string file_name):PartitionInfo(pid,file_name){};
	OneToManyPartitionInfo(PartitionID pid,string file_name,unsigned number_of_blocks):PartitionInfo(pid,file_name,number_of_blocks){
		for(int i=0;i<number_of_blocks;i++){
			block_to_node[i]=-1;
		}
	};
	binding_mode get_mode()const{
		return OneToMany;
	}
	void add_one_block(){
		number_of_blocks++;
		block_to_node[block_to_node.size()]=-1;
	}
	void add_mutiple_block(unsigned number_of_new_blocks){
		number_of_blocks+=number_of_new_blocks;
		for(unsigned i=0;i<number_of_new_blocks;i++){
			block_to_node[block_to_node.size()]=-1;
		}
	}
	bool bind_one_block(BlockID blockid,NodeID target){
		assert(target>=0&&blockid>0);
		block_to_node[blockid]=target;
		return true;
	}
	bool bind_all_blocks(NodeID target){
		assert(target>=0);
		for(int i=0;i<number_of_blocks;i++){
			block_to_node[i]=target;
		}
		return true;
	}
	bool is_all_blocks_bound(){
		hashmap<BlockID,NodeID>::iterator it=block_to_node.begin();
		while(it!=block_to_node.end()){
			if(it->second==-1)
				return false;
			it++;
		}
	}
	void unbind_all_blocks(){
		hashmap<BlockID,NodeID>::iterator it=block_to_node.begin();
		while(it!=block_to_node.end()){
			it->second=-1;
			it++;
		}
	}
	bool is_colocated(const PartitionInfo &)const;
	NodeID get_location() const{
		if(block_to_node.size()==0)
			return -1;
		const NodeID ret=block_to_node.at(0);
		for(unsigned i=1;i<block_to_node.size();i++){
			if(block_to_node.at(i)==-1||block_to_node.at(i)!=ret)
				return -1;
		}
		return ret;
	}
	virtual ~OneToManyPartitionInfo(){};
private:
	/*
	 * record which node is each block bound to. "NodeID=-1" means that the block has not been bound to any node.
	 */
	hashmap<BlockID,NodeID> block_to_node;

};


class Partitioner {
public:
	Partitioner(ProjectionID partition_id,unsigned number_of_partitions,PartitionFunction* partition_functin);
	Partitioner(ProjectionID partition_id,unsigned number_of_partitions,const Attribute &partition_key,PartitionFunction* partition_functin);
	virtual ~Partitioner();
	unsigned getNumberOfPartitions()const;

	/* bind a partition to a specific node*/
	bool bindPartitionToNode(PartitionOffset partition_id,NodeID target_node);

	/* unbind a partition from a pre-assigned node*/
	void unbindPartitionToNode(PartitionOffset partition_id);

	/* notify partitioner that a file is created on distributed file system for a specific partition*/
	void RegisterPartition(unsigned partitoin_key,unsigned number_of_chunks);

	unsigned getPartitionDataSize(unsigned partitoin_index)const;

	unsigned getPartitionChunks(unsigned partitoin_index)const;

	NodeID getPartitionLocation(unsigned partition_index)const;
	void print();

	bool hasSamePartitionLocation(const Partitioner & target_partition )const;

	binding_mode get_bing_mode_()const{
		return mode_;
	}
	PartitionFunction::partition_fashion getPartitionFashion()const;
	Attribute getPartitionKey()const;
	PartitionFunction* getPartitionFunction()const;
	ProjectionID getProejctionID()const;
	bool allPartitionBound()const;
private:
	Attribute* partition_key_;
	PartitionFunction* partition_functin_;
	unsigned number_of_partitions_;
	vector<PartitionInfo*> partition_info_list;
	binding_mode mode_;
	ProjectionID projection_id_;
//	hashmap<PartitionID,std::string> partitionid_to_filename_;
//	hashmap<PartitionID,pair<NodeID,vector<BlockInfo> > > partition_node_blockinfo_;
//
//
//	/* the map describes the nodeId, on which a given partition is or should be stored.*/
//	hashmap<PartitionID,NodeID> partitionid_to_nodeid_;
//
//	vector<PartitionInfo> partition_info_list;

};




#endif /* PARTITIONER_H_ */
