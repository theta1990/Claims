/*
 * ExpandableBlockStreamBroadcastExchange.h
 *	This class is implemented based on the ExchangeIteratorEager.
 *
 *  Created on: Aug 29, 2013
 *      Author: wangli
 */

#ifndef ExpandableBlockStreamBroadcastExchange_H_
#define ExpandableBlockStreamBroadcastExchange_H_



#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>
#include <string>
#include <pthread.h>

#include "../../Schema/Schema.h"
#include "../BlockStreamIteratorBase.h"
#include "../../Block/BlockReadable.h"
#include "../../Block/BlockReadableFixBuffer.h"
#include "../../Executor/IteratorExecutorMaster.h"
#include "../../Block/synch.h"
#include "../../Block/PartitionedBlockBuffer.h"
#include "../../Block/BlockStream.h"
#include "../../Block/BlockStreamBuffer.h"

class ExpandableBlockStreamBroadcastExchange:public BlockStreamIteratorBase {
public:
	struct State{
		Schema* schema;
		BlockStreamIteratorBase* child;
		unsigned block_size;
		unsigned long long int exchange_id;
		std::vector<std::string> lower_ip_list;
		std::vector<std::string> upper_ip_list;
		State(Schema* schema, BlockStreamIteratorBase* child,unsigned block_size,std::vector<std::string> lower_ip_list,std::vector<std::string> upper_ip_list,unsigned long long int exchange_id)
		:schema(schema),child(child),block_size(block_size),exchange_id(exchange_id),lower_ip_list(lower_ip_list),upper_ip_list(upper_ip_list){}
		State(){};
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			ar & schema & child & block_size & exchange_id & lower_ip_list & upper_ip_list;
		}

	};
	ExpandableBlockStreamBroadcastExchange(State state);
	ExpandableBlockStreamBroadcastExchange();
	virtual ~ExpandableBlockStreamBroadcastExchange();
	bool open(const PartitionOffset& partition_offset=0);
	bool next(BlockStreamBase* block);
	bool close();
private:
	bool PrepareTheSocket();
	bool RegisterExchange();
	bool isMaster();
	bool SerializeAndSendToMulti();
	bool WaitForConnectionFromLowerExchanges();
	bool CreateReceiverThread();
	void CancelReceiverThread();
	void SendBlockBufferedNotification(int target_socket_fd);
	void SendBlockAllConsumedNotification(int target_socket_fd);
	void CloseTheSocket();
//	int PickLowerOffset();
	static void* receiver(void* arg);
private:
	State state;
//	BlockReadable* curBlock;
	BlockReadable* block_for_socket_;
	BlockStreamBase* received_block_stream_;
	int sock_fd;
	unsigned socket_port;
	unsigned nlowers;
	int* socket_fd_lower_list;
	std::string * lower_ip_array;
	pthread_t receiver_tid;
//	semaphore empty_nslots;
//	semaphore used_nslots;
//	semaphore *produced_list;// one per lower exchange.
	unsigned nexhausted_lowers;
	semaphore sema_open_;
	volatile bool open_finished_;

	BlockStreamBuffer* buffer;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & boost::serialization::base_object<BlockStreamIteratorBase>(*this) & state;
	}
private:
	//debug
	unsigned consumed_block[100];
	unsigned received_block[100];

};

#endif /* EXCHANGEITERATOREAGER_H_ */
