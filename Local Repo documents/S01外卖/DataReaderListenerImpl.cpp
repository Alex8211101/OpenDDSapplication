#include "DataReaderListenerImpl.h"
#include "S01_SupermarketTypeSupportC.h"
#include "S01_SupermarketTypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <ace/streams.h>
#include<time.h>
#include <sys/timeb.h>
using namespace std;

void DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
{
	try {
		S01_Supermarket::DefaultInfDataReader_var reader_i = S01_Supermarket::DefaultInfDataReader::_narrow(reader);
		if (!reader_i) {
			std::cerr << "read: _narrow failed." << std::endl;
			return;
		}
		S01_Supermarket::DefaultInf S01_Supermarket_DefaultInf;
		DDS::SampleInfo si;
		DDS::ReturnCode_t status = reader_i->take_next_sample(S01_Supermarket_DefaultInf, si);
		if (status == DDS::RETCODE_OK) {
			printf("\n");
			//std::cout << "����Į������Է�С�鿪����ʾ������鿴������Ϣ��" << std::endl;
			//std::cout << "SampleInfo.sample_rank = " << si.sample_rank << std::endl;
			//std::cout << "SampleInfo.instance_state = " << si.instance_state << std::endl;
			if (si.valid_data)
			{
				time_t nowTime;
				time(&nowTime);
				struct timeb tb;
				ftime(&tb);
				std::cout << "[S01]��������Ϣ���=" << S01_Supermarket_DefaultInf.DefaultInfID << std::endl
					<< "[S01]�����ߺ��뼶��ʱ��" << S01_Supermarket_DefaultInf.ClockTime<< std::endl
					<< "   ��Ϣ���⣺ " << S01_Supermarket_DefaultInf.DefaultInfTopic << std::endl
					<< "====================================================================="<<std::endl 
					<< S01_Supermarket_DefaultInf.DefaultInfMessage << std::endl
					<< "=====================================================================" << std::endl 
					<< "��Ϣ��Դ��"<< S01_Supermarket_DefaultInf.PublisherName<< std::endl
					<< "[S01]������ʱ�䣺" << S01_Supermarket_DefaultInf.MTime
					<< "[S01]���ؽ���ʱ�䣺" << ctime(&nowTime) 
				    << "[S01]���ؽ��պ��뼶��ʱ��" << clock() << std::endl;
			}
			else if (si.instance_state == DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE)
			{
				std::cout << "��ǰʵ�����" << std::endl;
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
			std::cerr << "ERROR: read DefaultInf: Error: " << status << std::endl;
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
	std::cout << "���������ɻ�������" << std::endl;
}

void DataReaderListenerImpl::on_subscription_matched(
	DDS::DataReader_ptr,
	const DDS::SubscriptionMatchedStatus &)
{
	std::cout << "ƥ��ɹ���ƥ�����" << std::endl;
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