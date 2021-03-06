/*
 * iterator_remote_execute.cpp
 *
 *  Created on: Jun 22, 2013
 *      Author: wangli
 */

#include "../Executor/IteratorExecutorMaster.h"
#include "../Executor/IteratorExecutorSlave.h"
#include "../iterator.hpp"
#include "../iterator/SingleColumnScanIterator.h"
#include "../iterator/CombinedIterator.h"
#include "../iterator/FilterIterator.h"
#include "../iterator/AggregationIterator.h"
#include "../iterator/PrintIterator.h"

#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>
int mainRonaldo()
{
	int choice=0;
	printf("Master(0) or Slave(1) ?\n");
	choice=1;
	scanf("%d",&choice);

	if(choice==0)
	{


		///////////////////////////////////////////Scan////////////////////////////////////////|
		std::vector<column_type> column_list;
		column_list.push_back(column_type(t_int));

		Schema* input=new SchemaFix(column_list);
		Schema* output=new SchemaFix(column_list);
		SingleColumnScanIterator::State SCstate1("/home/imdb/temp/1_0.column",input, output);
		Iterator* scs1=new SingleColumnScanIterator(SCstate1);

		SingleColumnScanIterator::State SCstate2("/home/imdb/temp/1_1.column",input, output);
		Iterator* scs2=new SingleColumnScanIterator(SCstate2);

		SingleColumnScanIterator::State SCstate3("/home/imdb/temp/1_1.column",input, output);
		Iterator* scs3=new SingleColumnScanIterator(SCstate3);
		//---------------------------------------------------------------------------------------|


		///////////////////////////////////////////Combined////////////////////////////////////////|
		std::vector<Schema*> inputs;
		inputs.push_back(output);
		inputs.push_back(output);
		inputs.push_back(output);
		column_list.push_back(column_type(t_int));
		std::vector<column_type> column_list1;
		column_list1.push_back(column_type(t_int));
		column_list1.push_back(column_type(t_int));
		column_list1.push_back(column_type(t_int));
		Schema* outputs=new SchemaFix(column_list1);
		std::vector<Iterator*> children;
		children.push_back(scs1);
		children.push_back(scs2);
		children.push_back(scs3);

		CombinedIterator::State CIstate(inputs,outputs,children);
		Iterator* ci=new CombinedIterator(CIstate);

		//---------------------------------------------------------------------------------------|



		///////////////////////////////////////////Filter////////////////////////////////////////|
		FilterIterator::State FIstate;
		FIstate.child=ci;
		FIstate.input=outputs;
		FIstate.output=outputs;
		int f=0;

		FilterIterator::AttributeComparator filter1(column_type(t_int),Comparator::GEQ,0,&f);
		FIstate.ComparatorList.push_back(filter1);



		int f2=500;
		FilterIterator::AttributeComparator filter2(column_type(t_int),Comparator::L,1,&f2);
		FIstate.ComparatorList.push_back(filter2);
		Iterator* fi=new FilterIterator(FIstate);

		//----------------------------------------------------------------------------------------|

		///////////////////////////////////////Aggregation////////////////////////////////////|

		std::vector<unsigned> GroIndex;
		GroIndex.push_back(0);
	//	GroIndex.push_back(1);
		std::vector<unsigned> AggIndex;
		AggIndex.push_back(1);
		AggIndex.push_back(2);
		std::vector<AggregationIterator::State::aggregation> aggtype;
		aggtype.push_back(AggregationIterator::State::sum);
		aggtype.push_back(AggregationIterator::State::count);
		AggregationIterator::State AIstate(outputs,outputs,fi,GroIndex,AggIndex,aggtype,1024,48);
		Iterator* ai=new AggregationIterator(AIstate);


		//------------------------------------------------------------------------------------|

		///////////////////////////////////////Print///////////////////////////////////////////|


		PrintIterator::State PIstate(outputs,ai);
		Iterator *pi=new PrintIterator(PIstate);
		//-------------------------------------------------------------------------------------|

		std::ostringstream ostr;
		boost::archive::text_oarchive oa(ostr);
//	//	oa.register_type(static_cast<SingleColumnScanIterator *>(NULL));
//		Register_Schemas<boost::archive::text_oarchive>(oa);
//		Register_Iterators(oa);
//		oa<<pi;
//		std::cout<<"Serialization Result:"<<ostr.str()<<std::endl;
		IteratorExecutorMaster IEM;
		int d;
		printf("Enter 1 to continue, other number to stop.\n");
		scanf("%d",&d);
		while(d==1)
		{
//			IEM.ExecuteIteratorsOnSlave(pi);
			printf("Enter 1 to continue, other number to stop.\n");
			scanf("%d",&d);
		}
//		IteratorMessage IM(pi);
//		Message256 message= IteratorMessage::serialize(IM);
//		std::cout<<"Serialization Result:"<<message.message<<std::endl;
//		ostringstream ostr;
//		boost::archive::text_oarchive oa(ostr);
//		Register_Iterators(oa);
//		oa<<pi;

//		istringstream istr(ostr.str());
//
//		printf("%s\n",istr.str());


//		IEM.ExecuteIteratorsOnSlave(pi);



	}
	else
	{
		IteratorExecutorSlave IES;



	}
	printf("Go to sleep while!\n");
	while(1)
	{
		sleep(1);
	}
	return 1;
}

