#include "S03_TransferFileTypeSupportImpl.h"
#include <dds\DdsDcpsInfrastructureC.h>
#include <dds\DdsDcpsPublicationC.h>
#include <dds\DCPS\StaticIncludes.h>
#include <dds\DCPS\Service_Participant.h>
#include <dds\DCPS\Marked_Default_Qos.h>
//#include <dds\DCPS\PublisherImpl.h>
#include <dds\DCPS\WaitSet.h>
#include <ace\streams.h>
//#include <ace\OS_NS_unistd.h>
#include <ace\Log_Msg.h>
#include<iostream>
#include <sys/timeb.h>
#include<time.h>
using namespace std;


int main(int argc, char *argv[]) {
	char * input_p = CORBA::string_alloc(10086);
	string infs;
	char infs_array[50];
	
	strcpy(input_p, infs_array);
	try {


		char host[255];
		WSAData data;
		if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
		{
			cout << "初始化错误,无法获取主机信息..." << endl;
		}
		//获取主机名:也可以使用GetComputerName()这个函数
		if (gethostname(host, sizeof(host)) == SOCKET_ERROR)
		{
			cout << "无法获取主机名..." << endl;
		}
		else
		{
			//cout << "本机计算机名为:" << host << endl;
		}

		//注入点

		//初始化域参数工厂
		DDS::DomainParticipantFactory_var dpf =
			TheParticipantFactoryWithArgs(argc, argv);
		//创建域参数
		DDS::DomainParticipant_var participant =
			dpf->create_participant(42, // domain ID
				PARTICIPANT_QOS_DEFAULT,
				0,  // No listener required
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		//域参数创建异常处理
		if (!participant) {
			std::cerr << "create_participant failed." << std::endl;
			return 1;
		}
		//注册S03_TransferFile::FileMessage类型的类型支持类
		S03_TransferFile::FileMessageTypeSupport_var ts = new S03_TransferFile::FileMessageTypeSupportImpl;
		//注册异常处理
		if (DDS::RETCODE_OK != ts->register_type(participant, "")) {
			std::cerr << "register_type failed." << std::endl;
			return 1;
		}
		//创建主题（FileMessage S03_TransferFile）
		CORBA::String_var type_name = ts->get_type_name();
		DDS::Topic_var topic =
			participant->create_topic("FileMessage S03_TransferFile",
				type_name,
				TOPIC_QOS_DEFAULT,
				0,   // No listener required
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		//主题创建异常处理
		if (!topic) {
			std::cerr << "create_topic failed." << std::endl;
			return 1;
		}
		
		//等待集设定
		/*DDS::StatusCondition_var condition = writer->get_statuscondition();
		condition->set_enabled_statuses(DDS::PUBLICATION_MATCHED_STATUS);
		DDS::WaitSet_var ws = new DDS::WaitSet;
		ws->attach_condition(condition);
		while (true)
		{
			DDS::PublicationMatchedStatus matches;
			if (writer->get_publication_matched_status(matches) != ::DDS::RETCODE_OK)
			{
				std::cerr << "get_publication_matched_status failed." << std::endl;
				return 1;
			}
			//等待集中有实例
			if (matches.current_count >= 1)
			{
				break;
			}
			DDS::ConditionSeq conditions;
			//等待时间为60秒
			DDS::Duration_t timeout = { 60, 0 };
			if (ws->wait(conditions, timeout) != DDS::RETCODE_OK)
			{
				std::cerr << "wait failed" << std::endl;
				return 1;
			}
		}
		ws->detach_condition(condition);*/
		
		cout << argc << endl;
		int S02_FileMessageCount = 0;
		int AuthorID = 0;
		while (1)
		{
			
			//创建发布者
			DDS::Publisher_var pub =
				participant->create_publisher(PUBLISHER_QOS_DEFAULT,
					0,    // No listener required
					OpenDDS::DCPS::DEFAULT_STATUS_MASK);
			//发布者创建异常处理
			if (!pub) {
				std::cerr << "create_publisher failed." << std::endl;
				return 1;
			}
			//创建数据写者
			DDS::DataWriter_var writer =
				pub->create_datawriter(topic,
					DATAWRITER_QOS_DEFAULT,
					0,    // No listener required
					OpenDDS::DCPS::DEFAULT_STATUS_MASK);
			//数据写者创建异常
			if (!writer) {
				std::cerr << "create_datawriter failed." << std::endl;
				return 1;
			}
			//类型窄化
			S03_TransferFile::FileMessageDataWriter_var FileMessage_writer = S03_TransferFile::FileMessageDataWriter::_narrow(writer);
			//写入数据样本
			S03_TransferFile::FileMessage FileMessage;
			memset(infs_array, 0, sizeof(infs_array));
			cout << "请输入你要传输的文件名（请确保它存在，完整的和后缀一起） :" << endl;
			cin >> infs_array;
			if (strcmp(infs_array, "#")==0) break;
			FILE *fp;
			fp = fopen(infs_array, "rb");
			if (fp)
			{
				char *FilePtr;
				int len = filelength(fileno(fp));
				FilePtr=(char*)malloc(len * sizeof(char));
				fread(FilePtr, sizeof(char), len, fp);
				FileMessage.CatchedFile = FilePtr;
				FileMessage.FileLength = len;
				FileMessage.OFile.length(len);
				memcpy(&FileMessage.OFile[0], FilePtr, len);
				cout << "读取文件成功，正在传输..." << endl;
				/*string s;
				fseek(fp, 0, SEEK_END);
				int len = ftell(fp);
				fseek(fp, 0, SEEK_SET);
				s.resize(len);
				fread((void*)s.data(), 1, len, fp);
				fclose(fp);
				CORBA::String_var s_File = CORBA::string_dup(s.c_str());
				FileMessage.CatchedFile= s_File;
				FileMessage.FileLength = len;
				FileMessage.OFile.get_buffer(s.c_str());
				//cout << "st读取文件内容为：" << ss << endl;
				//cout<<"读取文件内容为：" << FileMessage.CatchedFile << endl;*/
				fclose(fp);
			}
			else
			{
				cout<<"输入的文件名找不到，请重新输入哦" << endl;
				continue;
			}
			
			time_t nowTime;
			time(&nowTime);
			struct timeb tb;     
			ftime(&tb);
			CORBA::String_var s_Name = CORBA::string_dup(host);
			CORBA::String_var s_Inf = CORBA::string_dup(infs_array);
			CORBA::String_var s_Time = CORBA::string_dup(ctime(&nowTime));
			FileMessage.FileMessageID = AuthorID;
			FileMessage.PublisherName = s_Name;
			FileMessage.PublishMessage = s_Inf;
			FileMessage.MTime = s_Time;//ctime(&nowTime);
			FileMessage.ClockTime = clock();
			//FileMessage.OFile;
			//FileMessage.CatchedFile= "Not Successful.";
			DDS::ReturnCode_t error = FileMessage_writer->write(FileMessage, DDS::HANDLE_NIL);
			AuthorID++;
			if (error != DDS::RETCODE_OK) {
				std::cerr << "write failed." << std::endl;
				//return 1;
				break;
			}
			//等待样本被接收确认
			DDS::Duration_t timeout = { 30, 0 };
			if (writer->wait_for_acknowledgments(timeout) != DDS::RETCODE_OK)
			{
				std::cerr << "wait_for_acknowledgments failed." << std::endl;
				//return 1;
				break;
			}
			DDS::WaitSet_var ws = new DDS::WaitSet;
			DDS::StatusCondition_var condition = writer->get_statuscondition();
			ws->attach_condition(condition);

			DDS::ConditionSeq conditions;
			if (ws->wait(conditions, timeout) != DDS::RETCODE_OK)
			{
				std::cerr << "wait failed" << std::endl;
				return 1;
			}
		}
		


			
		
		//实例清理
		participant->delete_contained_entities();
		dpf->delete_participant(participant);
		TheServiceParticipant->shutdown();
	}
	catch (CORBA::Exception& e) {
		cerr << "Exception caught in main.cpp:" << endl
			<< e << endl;
		ACE_OS::exit(1);
	}
	return 0;
}