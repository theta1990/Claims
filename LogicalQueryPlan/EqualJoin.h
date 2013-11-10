/*
 * EqualJoin.h
 *
 *  Created on: Nov 10, 2013
 *      Author: wangli
 */

#ifndef EQUALJOIN_H_
#define EQUALJOIN_H_
#include <vector>
#include "LogicalOperator.h"
#include "../Catalog/Attribute.h"
class EqualJoin:public LogicalOperator {
	struct JoinPair{
		JoinPair(Attribute &a,Attribute & b):first(a),second(b){};
		Attribute first;
		Attribute second;
	};
	enum JoinPolice{na,no_repartition,left_repartition,right_repartition,complete_repartition};
public:
	EqualJoin(std::vector<JoinPair>,LogicalOperator* left_input,LogicalOperator* right_input);
	virtual ~EqualJoin();
	Dataflow getDataflow();

private:
	bool isHashOnLeftKey(const Partitioner& part,const Attribute& key)const;

	/*check whether the partitioning is based on hash and the hash key is a subset of the join keys such that hash join
	 * is enabled.
	 */
	bool canLeverageHashPartition(const std::vector<Attribute> &partition_key_list,const DataflowPartitionDescriptor& partitoiner)const;

	/** current version only consider the data size for simplicity.
	 * TODO: consider not only data size but also other factors, such as parallelism, resource, etc.**/
	JoinPolice decideLeftOrRightRepartition(const Dataflow& left_dataflow,const Dataflow& right_dataflow)const;
private:
	std::vector<JoinPair> joinkey_pair_list_;
	std::vector<Attribute> left_join_key_list_;
	std::vector<Attribute> right_join_key_list_;
	LogicalOperator* left_child_;
	LogicalOperator* right_child_;
	JoinPolice join_police_;

};

#endif /* EQUALJOIN_H_ */