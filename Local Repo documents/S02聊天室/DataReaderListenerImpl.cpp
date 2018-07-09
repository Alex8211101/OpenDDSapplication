#include "DataReaderListenerImpl.h"
#include "S02_ChatRoomTypeSupportC.h"
#include "S02_ChatRoomTypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <ace/streams.h>
#include<time.h>
#include <sys/timeb.h>
using namespace std;

void DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
{
	time_t nowTime;
	time(&nowTime);

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

	try {
		S02_ChatRoom::MessageDataReader_var reader_i = S02_ChatRoom::MessageDataReader::_narrow(reader);
		if (!reader_i) {
			std::cerr << "read: _narrow failed." << std::endl;
			return;
		}
		S02_ChatRoom::Message S02_ChatRoom_pos;
		DDS::SampleInfo si;
		DDS::ReturnCode_t status = reader_i->take_next_sample(S02_ChatRoom_pos, si);
		if (status == DDS::RETCODE_OK) {
			std::cout << "SampleInfo.sample_rank = " << si.sample_rank << std::endl;
			std::cout << "SampleInfo.instance_state = " << si.instance_state << std::endl;
			if (si.valid_data/*&&S02_ChatRoom_pos.PublisherName.in()!=host*/)
			{
				time_t nowTime;
				time(&nowTime);
				struct timeb tb;
				ftime(&tb);
				std::cout << std::endl << "[S02]��������Ϣ��ţ�"<< S02_ChatRoom_pos.MessageID << std::endl
					<< "[S02]�����ߺ��뼶��ʱ��" << S02_ChatRoom_pos.Mtime << std::endl
					<< "[S02]������������: " << S02_ChatRoom_pos.PublisherName << std::endl
					<< "==================================================" << std::endl
					<< S02_ChatRoom_pos.MessageInf << std::endl
					<< "==================================================" << std::endl
					<< "[S02]������ʱ�䣺" << S02_ChatRoom_pos.SendTime  
					<< "[S02]���ؽ���ʱ�䣺" <<  ctime(&nowTime) 
					<< "[S02]���ؽ��պ��뼶��ʱ��" << clock() << std::endl;
			}
			/*else if (si.valid_data&&S02_ChatRoom_pos.PublisherName.in() == host)
			{

			}*/
			else if (si.instance_state == DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE)
			{
				std::cout << "instance is disS02_ChatRoom_posed" << std::endl;
			}
			else if (si.instance_state == DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE)
			{
				std::cout << "instance is unregistered" << std::endl;
			}
			else
			{
				std::cerr << "ERROR: received unknown instance state "
					<< si.instance_state << std::endl;
			}
		}
		else if (status == DDS::RETCODE_NO_DATA) {
			std::cerr << "ERROR: reader received DDS::RETCODE_NO_DATA!" << std::endl;
		}
		else {
			std::cerr << "ERROR: read Message: Error: " << status << std::endl;
		}
	}
	catch (CORBA::Exception& e) {
		std::cerr << "Exception caught in main.cpp:" << std::endl
			<< e << std::endl;
		ACE_OS::exit(1);
	}

}

void DataReaderListenerImpl::on_requested_deadline_missed(
	DDS::DataReader_ptr,
	const DDS::RequestedDeadlineMissedStatus &)
{
	std::cerr << "DataReaderListenerImpl::on_requested_deadline_missed" << std::endl;
}

void DataReaderListenerImpl::on_requested_incompatible_qos(
	DDS::DataReader_ptr,
	const DDS::RequestedIncompatibleQosStatus &)
{
	std::cerr << "DataReaderListenerImpl::on_requested_incompatible_qos" << std::endl;
}

void DataReaderListenerImpl::on_liveliness_changed(
	DDS::DataReader_ptr,
	const DDS::LivelinessChangedStatus &)
{
	std::cerr << "DataReaderListenerImpl::on_liveliness_changed" << std::endl;
}

void DataReaderListenerImpl::on_subscription_matched(
	DDS::DataReader_ptr,
	const DDS::SubscriptionMatchedStatus &)
{
	std::cerr << "DataReaderListenerImpl::on_subscription_matched" << std::endl;
}

void DataReaderListenerImpl::on_sample_rejected(
	DDS::DataReader_ptr,
	const DDS::SampleRejectedStatus&)
{
	std::cerr << "DataReaderListenerImpl::on_sample_rejected" << std::endl;
}

void DataReaderListenerImpl::on_sample_lost(
	DDS::DataReader_ptr,
	const DDS::SampleLostStatus&)
{
	std::cerr << "DataReaderListenerImpl::on_sample_lost" << std::endl;
}