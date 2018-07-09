#include "YH02TypeSupportImpl.h"
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
#include <sys/timeb.h>
#include<time.h>
using namespace std;
int main(int argc, char *argv[]) {
	try {

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
		//ע��YH02::M02���͵�����֧����
		YH02::M02TypeSupport_var ts = new YH02::M02TypeSupportImpl;
		//ע���쳣����
		if (DDS::RETCODE_OK != ts->register_type(participant, "")) {
			std::cerr << "register_type failed." << std::endl;
			return 1;
		}
		//�������⣨M02 YH02��
		CORBA::String_var type_name = ts->get_type_name();
		DDS::Topic_var topic =
			participant->create_topic("M02 YH02",
				type_name,
				TOPIC_QOS_DEFAULT,
				0,   // No listener required
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		//���ⴴ���쳣����
		if (!topic) {
			std::cerr << "create_topic failed." << std::endl;
			return 1;
		}
		//��������2��M02 YH02��
		DDS::Topic_var topic2 =
			participant->create_topic("M02 YH02SELL",
				type_name,
				TOPIC_QOS_DEFAULT,
				0,   // No listener required
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		//���ⴴ���쳣����
		if (!topic2) {
			std::cerr << "create_topic2 failed." << std::endl;
			return 1;
		}
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
		YH02::M02DataWriter_var M02_writer = YH02::M02DataWriter::_narrow(writer);
		//д����������
		YH02::M02 M02;
		M02.YH02_M02_ID = 0;
		M02.YH02_M02_double = 3.15;
		M02.YH02_M02_string  = "С�ײ�";
		std::cout << "��ʼ���������˼�" << std::endl;
		for (int i = 0; i < 3; ++i) {
				if(i==0){
				M02.YH02_M02_string  = "С�ײ�";
			}
			if(i==1){
				M02.YH02_M02_string  = "���Ĳ�";
			}
			if(i==2){
				M02.YH02_M02_string  = "���ܲ�";
			}
			std::cout << "��Ʒ���ƣ�  "<<M02.YH02_M02_string<< std::endl;
			std::cout << "�����Ʒ�����۸�  "<<std::endl;
			scanf("%lf",&M02.YH02_M02_double);
			time_t nowTime;
			time(&nowTime);
			struct timeb tb;
			ftime(&tb);
			CORBA::String_var s_Time = CORBA::string_dup(ctime(&nowTime));
			M02.LocalTime = s_Time;
			M02.ClockTime = clock();
		DDS::ReturnCode_t error = M02_writer->write(M02, DDS::HANDLE_NIL);
			++M02.YH02_M02_ID;
			if (error != DDS::RETCODE_OK) {
				std::cerr << "write failed." << std::endl;
				return 1;
			}
		}
		//�ȴ�����������ȷ��
		DDS::Duration_t timeout = { 30, 0 };
		if (writer->wait_for_acknowledgments(timeout) != DDS::RETCODE_OK)
		{
			std::cerr << "wait_for_acknowledgments failed." << std::endl;
			return 1;
		}
		//����д��2
		DDS::DataWriter_var writer2 =
			pub->create_datawriter(topic2,
				DATAWRITER_QOS_DEFAULT,
				0,    // No listener required
				OpenDDS::DCPS::DEFAULT_STATUS_MASK);
		//����д�ߴ����쳣
		if (!writer2) {
			std::cerr << "create_datawriter failed." << std::endl;
			return 1;
		}
		//����խ��
		YH02::M02DataWriter_var M02_writer2 = YH02::M02DataWriter::_narrow(writer2);
		//д����������
		M02.YH02_M02_ID = 0;
		M02.YH02_M02_double = 3;
		M02.YH02_M02_string  = "С�ײ�";
		std::cout << "��ʼ����" << std::endl;
		for (int i = 0; i < 3; ++i) {
			if(i==0){
				M02.YH02_M02_string  = "С�ײ�";
			}
			if(i==1){
				M02.YH02_M02_string  = "���Ĳ�";
			}
			if(i==2){
				M02.YH02_M02_string  = "���ܲ�";
			}
			std::cout << "��ǰ��Ʒ��  "<< M02.YH02_M02_string<<std::endl;
			std::cout << "�����Ʒ���ۼ۸�  "<<std::endl;
			scanf("%lf",&M02.YH02_M02_double);
			time_t nowTime;
			time(&nowTime);
			struct timeb tb;
			ftime(&tb);
			CORBA::String_var s_Time = CORBA::string_dup(ctime(&nowTime));
			M02.LocalTime = s_Time;
			M02.ClockTime = clock();
		DDS::ReturnCode_t error = M02_writer2->write(M02, DDS::HANDLE_NIL);
			++M02.YH02_M02_ID;
			if (error != DDS::RETCODE_OK) {
				std::cerr << "write failed." << std::endl;
				return 1;
			}
		}
		//�ȴ�����������ȷ��
		DDS::Duration_t timeout2 = { 30, 0 };
		if (writer2->wait_for_acknowledgments(timeout2) != DDS::RETCODE_OK)
		{
			std::cerr << "wait_for_acknowledgments failed." << std::endl;
			return 1;
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