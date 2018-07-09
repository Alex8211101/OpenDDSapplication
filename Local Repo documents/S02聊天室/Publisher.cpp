#include "S02_ChatRoomTypeSupportImpl.h"
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
			cout << "��ʼ������,�޷���ȡ������Ϣ..." << endl;
		}
		//��ȡ������:Ҳ����ʹ��GetComputerName()�������
		if (gethostname(host, sizeof(host)) == SOCKET_ERROR)
		{
			cout << "�޷���ȡ������..." << endl;
		}
		else
		{
			//cout << "�����������Ϊ:" << host << endl;
		}

		//ע���

		//��ʼ�����������
		DDS::DomainParticipantFactory_var dpf =
			TheParticipantFactoryWithArgs(argc, argv);
		//���������
		DDS::DomainParticipant_var participant =
			dpf->create_participant(42, // domain ID
				PARTICIPANT_QOS_DEFAULT,
				0,  // No listener required
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		//����������쳣����
		if (!participant) {
			std::cerr << "create_participant failed." << std::endl;
			return 1;
		}
		//ע��S02_ChatRoom::Message���͵�����֧����
		S02_ChatRoom::MessageTypeSupport_var ts = new S02_ChatRoom::MessageTypeSupportImpl;
		//ע���쳣����
		if (DDS::RETCODE_OK != ts->register_type(participant, "")) {
			std::cerr << "register_type failed." << std::endl;
			return 1;
		}
		//�������⣨Message S02_ChatRoom��
		CORBA::String_var type_name = ts->get_type_name();
		DDS::Topic_var topic =
			participant->create_topic("Message S02_ChatRoom",
				type_name,
				TOPIC_QOS_DEFAULT,
				0,   // No listener required
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		//���ⴴ���쳣����
		if (!topic) {
			std::cerr << "create_topic failed." << std::endl;
			return 1;
		}
		
		//�ȴ����趨
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
			//�ȴ�������ʵ��
			if (matches.current_count >= 1)
			{
				break;
			}
			DDS::ConditionSeq conditions;
			//�ȴ�ʱ��Ϊ60��
			DDS::Duration_t timeout = { 60, 0 };
			if (ws->wait(conditions, timeout) != DDS::RETCODE_OK)
			{
				std::cerr << "wait failed" << std::endl;
				return 1;
			}
		}
		ws->detach_condition(condition);*/
		
		cout << argc << endl;
		int S02_MessageCount = 0;
		int AuthorID = 0;
		while (1)
		{
			
			//����������
			DDS::Publisher_var pub =
				participant->create_publisher(PUBLISHER_QOS_DEFAULT,
					0,    // No listener required
					OpenDDS::DCPS::DEFAULT_STATUS_MASK);
			//�����ߴ����쳣����
			if (!pub) {
				std::cerr << "create_publisher failed." << std::endl;
				return 1;
			}
			//��������д��
			DDS::DataWriter_var writer =
				pub->create_datawriter(topic,
					DATAWRITER_QOS_DEFAULT,
					0,    // No listener required
					OpenDDS::DCPS::DEFAULT_STATUS_MASK);
			//����д�ߴ����쳣
			if (!writer) {
				std::cerr << "create_datawriter failed." << std::endl;
				return 1;
			}
			//����խ��
			S02_ChatRoom::MessageDataWriter_var Message_writer = S02_ChatRoom::MessageDataWriter::_narrow(writer);
			//д����������
			S02_ChatRoom::Message Message;
			memset(infs_array, 0, sizeof(infs_array));
			cout << "Please type your information :" << endl;
			cin >> infs_array;
			if (strcmp(infs_array, "#")==0) break;
			time_t nowTime;
			time(&nowTime);
			struct timeb tb;     
			ftime(&tb);
			CORBA::String_var s_Name = CORBA::string_dup(host);
			CORBA::String_var s_Inf = CORBA::string_dup(infs_array);
			CORBA::String_var s_Time = CORBA::string_dup(ctime(&nowTime));
			Message.MessageID = AuthorID;
			Message.PublisherName = s_Name;
			Message.MessageInf = s_Inf;
			Message.SendTime = s_Time;//ctime(&nowTime);
			Message.Mtime = clock();
			DDS::ReturnCode_t error = Message_writer->write(Message, DDS::HANDLE_NIL);
			AuthorID++;
			if (error != DDS::RETCODE_OK) {
				std::cerr << "write failed." << std::endl;
				//return 1;
				break;
			}
			//�ȴ�����������ȷ��
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
		


			
		
		//ʵ������
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