/*
 * BlockManager.cpp
 *
 *  Created on: 2013-10-11
 *      Author: casa
 */

#include "BlockManager.h"

BlockManager *BlockManager::blockmanager_=0;

BlockManager *BlockManager::getInstance(BlockManagerWorkerActor *worker){
	if(blockmanager_==0){
		blockmanager_=new BlockManager(worker);
	}
	return blockmanager_;
}

BlockManager::~BlockManager() {

}

void BlockManager::initialize(){
	// 读配置文件中的配置，然后根据是否是master注册
	// 1，建两个存储，一个是内存的，一个磁盘的
	diskstore_=new DiskStore(DISKDIR);
	memstore_=new MemoryStore();
	blockManagerId_=new BlockManagerId();
	// 2，注册
	registerToMaster(blockManagerId_);
	// 3，开启心跳监听
	heartBeat();
}

void BlockManager::registerToMaster(BlockManagerId *blockManagerId){
	worker_->_reigisterToMaster(blockManagerId);
}

void BlockManager::heartBeat(){
	// 向master发送心跳信息,3秒一次，在此必须开一个新的线程
//	while(true){
		// 可以在这里有个配置property的指定，然后优化网络
//		sleep(3);
		worker_->_sendHeartBeat();
//	}
	reregister();
}

void BlockManager::reregister(){
	// 当storage节点出现失联，在再次注册的时候要上报block的信息,包括blockId和block的storageLevel
	reportAllBlocks();
}

void BlockManager::asyncReregister(){
	// 在put进去本地的存储的时候突然失联，重新注册，和一般失联会有区别
}

void BlockManager::reportAllBlocks(){
	// 在此函数中有个for循环将这个节点中的每个block的信息都上报
	// 与其作对比的还有reportBlockStatus函数，这个函数一般在block的状态有所变化的时候
	// 调用，reportBlockStatus里面还是会调用tryToReportBlockStatus如果不成功
	// 就重新开始注册
}

bool BlockManager::reportBlockStatus(string blockId){
	if(!tryToReportBlockStatus(blockId)){
		asyncReregister();
	}
	return true;
}

// 向master发送blocks的信息，当收到master的回应的时候
bool BlockManager::tryToReportBlockStatus(string blockId){
	worker_->_reportBlockStatus(blockId);
	return true;
}


void BlockManager::get(string blockId){
	getLocal(blockId);
}

void* BlockManager::getLocal(string blockId){
	void *rt=0;
	bool exists=false;
	map<string, BlockInfo*>::iterator it_;
	it_=blockInfoPool_.find(blockId);
	if(it_!=blockInfoPool_.end()){
		exists=true;
	}
	if(exists){
		// 如果存在就代表文件从hdfs上已经被拉到local了
		if((*it_).second->level_==BlockManager::memory){
			// spark中的storageLevel是磁盘和内存中都有的，在storageLevel.scala中
			// 我们有那样的应用吗？todo: 在此预留的序列化和反序列化接口，序列化与否也是
			// 在storageLevel中的，是否备份也是在storageLevel中
			rt=memstore_->getValue(blockId);
			return rt;
			// 这里不需要再判断是否在内存中了
		}
		if((*it_).second->level_==BlockManager::disk){
			// todo: 将磁盘上的数据load到内存中返回，将指针再次存储在内存中
		}
	}
	else{
		// 还不在local上面，此时就要调用函数从hdfs上取
		cout<<"the chunkId is not registered locally, it's on the hdfs!"<<endl;
		ChunkInfo ci=loadFromHdfs(blockId);
		put(blockId,BlockManager::memory,ci.hook);
		rt=ci.hook;
	}
	return rt;
}

bool BlockManager::put(string blockId,storageLevel level,void* value){
	// 由于stroageLevel的单一，所以put也比较简单，put里面直接加上blockId的value
	// replication和serialization都没有考虑进去 todo: 数据在内存中的备份
	BlockInfo *bi=new BlockInfo(level);
	blockInfoPool_[blockId.c_str()]=bi;
	if(level==BlockManager::memory){
		memstore_->putValue(blockId,value);
		// 在这一层中，storageLevel就没有了，但是在spark中是有的，因在此比较单一
	}
	if(level==BlockManager::disk){
		diskstore_->putValue(blockId,value);
	}
	reportBlockStatus(blockId);
	return true;
}

//// 这个函数返回一个构造好的chunkid和每个chunk的指针
//// 这个里面的chunkId肯定是要在blockManager注册然后汇报信息的
//// put的话也是会这样的，可以将这个函数中调用put然后统一汇报信息的接口
//vector<ChunkInfo> BlockManager::loadFromHdfs(string file_name){
//	// 由此函数得到的<blockId,指针>
//	vector<ChunkInfo> vci;
//	map<string, void *>::iterator it_;
//	it_=bufferpool_.find(file_name);
//	if(it_!=bufferpool_.end()){
////		rt=bufferpool_[file_name];
//	}
//	else{
//		hdfsFS fs=hdfsConnect(HDFS_N,9000);
//		hdfsFile readFile=hdfsOpenFile(fs,file_name.c_str(),O_RDONLY,0,0,0);
//		hdfsFileInfo *hdfsfile=hdfsGetPathInfo(fs,file_name.c_str());
////		char ***path=hdfsGetHosts(fs,"/home/hayue/input/3_64m",0,201326592+12);
//		cout<<"file size: "<<hdfsfile->mSize<<endl;
//		if(!readFile){
//			cout<<"open file error"<<endl;
//		}
//		unsigned length=0;
//		int offset=0;
//		while(length<hdfsfile->mSize){
//			ChunkInfo ci;
//			void *rt=malloc(CHUNK_SIZE);
//			tSize bytes_num=hdfsPread(fs,readFile,length,rt,CHUNK_SIZE);
//			cout<<"split interface: "<<bytes_num<<endl;
//			ostringstream chunkid;
//			chunkid<<file_name.c_str()<<"_"<<offset++;
//			ci.chunkId=chunkid.str().c_str();
//			ci.hook=rt;
//			vci.push_back(ci);
//			cout<<ci.chunkId.c_str()<<"---"<<length<<endl;
//			length=length+CHUNK_SIZE;
//		}
////		hdfsSeek(fs,readFile,CHUNK_SIZE);
//		hdfsCloseFile(fs,readFile);
////		cout<<bytes_num<<endl;
////		bufferpool_[file_name]=rt;
//	}
//	return vci;
//}

// 这个函数返回一个构造好的chunkid和每个chunk的指针
// 这个里面的chunkId肯定是要在blockManager注册然后汇报信息的
// put的话也是会这样的，可以将这个函数中调用put然后统一汇报信息的接口
ChunkInfo BlockManager::loadFromHdfs(string file_name){
	// 由此函数得到的<blockId,指针>
	ChunkInfo ci;
	string file_name_former,file_name_latter;
	unsigned pos=file_name.rfind("$");
	file_name_former=file_name.substr(0,pos);
	file_name_latter=file_name.substr(pos+1,file_name.length());
	int offset=atoi(file_name_latter.c_str());
	hdfsFS fs=hdfsConnect(HDFS_N,9000);
	hdfsFile readFile=hdfsOpenFile(fs,file_name_former.c_str(),O_RDONLY,0,0,0);
	hdfsFileInfo *hdfsfile=hdfsGetPathInfo(fs,file_name_former.c_str());
	if(!readFile){
		cout<<"open file error"<<endl;
	}
	unsigned length=0;
	length=length+CHUNK_SIZE*offset;
	if(length<hdfsfile->mSize){
		void *rt=malloc(CHUNK_SIZE);
		tSize bytes_num=hdfsPread(fs,readFile,length,rt,CHUNK_SIZE);
		ostringstream chunkid;
		chunkid<<file_name.c_str()<<"$"<<offset;
		ci.chunkId=chunkid.str().c_str();
		ci.hook=rt;
	}else{
		ostringstream chunkid;
		chunkid<<file_name.c_str()<<"$"<<offset;
		ci.chunkId=chunkid.str().c_str();
		ci.hook=0;
	}
	hdfsCloseFile(fs,readFile);
	hdfsDisconnect(fs);
	return ci;
}

BlockManagerId *BlockManager::getId(){
	return blockManagerId_;
}

string BlockManager::askForMatch(string filename, BlockManagerId bmi){
	if(!file_proj_.count(filename.c_str())){
		string rt=worker_->_askformatch(filename,bmi);
		file_proj_[filename.c_str()]=rt;
	}
	return file_proj_[filename.c_str()];
}

BlockManager::BlockManagerWorkerActor::BlockManagerWorkerActor(Theron::EndPoint *endpoint,Theron::Framework *framework,const char * name)
:Actor(*framework,name),endpoint_(endpoint),framework_(framework){
	RegisterHandler(this,&BlockManagerWorkerActor::getBlock);
	RegisterHandler(this,&BlockManagerWorkerActor::putBlock);
}

BlockManager::BlockManagerWorkerActor::~BlockManagerWorkerActor() {

}

bool BlockManager::BlockManagerWorkerActor::_reigisterToMaster(BlockManagerId *bMId){
	cout<<"in the worker actor to register"<<endl;
	// 在注册的时候，就有receiverId的构造，也就是用这个string来作为所有的stroage node的标志，
	// 不会出现冲突，是因为传输的message是不一样的，
	receiverId_=bMId->blockManagerId;
	RegisterStorageMessage rsm(receiverId_.c_str());
	tor_=new TimeOutReceiver(endpoint_,receiverId_.c_str());
	Theron::Catcher<RegisterStorageRespond> resultCatcher;
	tor_->RegisterHandler(&resultCatcher, &Theron::Catcher<RegisterStorageRespond>::Push);
	framework_->Send(rsm,tor_->GetAddress(),Theron::Address("blockManagerMasterActor"));
	// TimeOutWait(count,time_out),如果返回的数值小于count,那就是超时了
	if(tor_->TimeOutWait(1,1000)==1){
		cout<<"register respond"<<endl;
		return true;
	}else{
		cout<<"not receive the register respond"<<endl;
		return false;
	}
}

bool BlockManager::BlockManagerWorkerActor::_sendHeartBeat(){
	string alive="I am ok";
	HeartBeatMessage hbm(alive.c_str());
	Theron::Catcher<HeartBeatRespond> resultCatcher;
	tor_->RegisterHandler(&resultCatcher, &Theron::Catcher<HeartBeatRespond>::Push);
	framework_->Send(hbm,tor_->GetAddress(),Theron::Address("blockManagerMasterActor"));
	// TimeOutWait(count,time_out),如果返回的数值小于count,那就是超时了
	if(tor_->TimeOutWait(1,1000)==1){
		cout<<"heartbeat respond"<<endl;
		return true;
	}else{
		cout<<"not receive heartbeat respond"<<endl;
		return false;
	}
}

bool BlockManager::BlockManagerWorkerActor::_reportBlockStatus(string blockId){
	BlockStatusMessage bsm(blockId.c_str());
	Theron::Catcher<BlockStatusRespond> resultCatcher;
	tor_->RegisterHandler(&resultCatcher, &Theron::Catcher<BlockStatusRespond>::Push);
	framework_->Send(bsm,tor_->GetAddress(),Theron::Address("blockManagerMasterActor"));
	// TimeOutWait(count,time_out),如果返回的数值小于count,那就是超时了
	if(tor_->TimeOutWait(1,1000)==1){
		cout<<"block status respond"<<endl;
		return true;
	}else{
		cout<<"not receive block status respond"<<endl;
		return false;
	}
}

string BlockManager::BlockManagerWorkerActor::_askformatch(string filename,BlockManagerId bmi){
	MatcherMessage mm(filename.c_str(),bmi.blockManagerId.c_str());
	Theron::Catcher<MatcherRespond> resultCatcher;
	tor_->RegisterHandler(&resultCatcher, &Theron::Catcher<MatcherRespond>::Push);
	framework_->Send(mm,tor_->GetAddress(),Theron::Address("blockManagerMasterActor"));
	// TimeOutWait(count,time_out),如果返回的数值小于count,那就是超时了
	cout<<"already send the message of matcher out"<<endl;
	if(tor_->TimeOutWait(1,1000)==1){
		cout<<"matcher respond"<<endl;
		MatcherRespond mr("");
		Theron::Address addr("blockManagerMasterActor");
		resultCatcher.Pop(mr,addr);
		cout<<"the receiver string is: "<<mr.mText<<endl;
		return mr.mText;
	}else{
		cout<<"not receive matcher respond"<<endl;
	}
}
