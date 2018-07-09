#include "DataReaderListenerImpl.h"
#include "YH02TypeSupportC.h"
#include "YH02TypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <ace/streams.h>
#include <sys/timeb.h>
#include<iostream>
#include<time.h>
using namespace std;

void DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
{
	try {
		YH02::M02DataReader_var reader_i = YH02::M02DataReader::_narrow(reader);
		if (!reader_i) {
			std::cerr << "read: _narrow failed." << std::endl;
			return;
		}
		YH02::M02 YH02_M02;
		DDS::SampleInfo si;
		DDS::ReturnCode_t status = reader_i->take_next_sample(YH02_M02, si);
		if (status == DDS::RETCODE_OK) {
			printf("\n");
			std::cout << "�ɹ����ܵ������Ĳ˼�" << std::endl;
			//std::cout << "SampleInfo.sample_rank = " << si.sample_rank << std::endl;
			//std::cout << "SampleInfo.instance_state = " << si.instance_state << std::endl;
			if (si.valid_data)
			{
				time_t nowTime;
				time(&nowTime);
				struct timeb tb;
				ftime(&tb);
				std::cout << std::endl << "[S04]��������Ϣ��ţ�" << YH02_M02.YH02_M02_ID << std::endl
					<< "[S04]�����ߺ��뼶��ʱ��" << YH02_M02.ClockTime << std::endl;
				cout << "==================================================" << std::endl;
				std::cout << "  ��Ʒ��� = " << YH02_M02.YH02_M02_ID << std::endl
					<< "   ��Ʒ����= " << YH02_M02.YH02_M02_string << std::endl
					<< "   ��Ʒ�ۼ�= " << YH02_M02.YH02_M02_double << std::endl;
				cout << "==================================================" << std::endl
					<< "[S04]�����߷���ʱ�䣺" << YH02_M02.LocalTime 
					<< "[S04]���ؽ���ʱ�䣺" << ctime(&nowTime) 
					<< "[S04]������Ϣ���պ��뼶��ʱ��" << clock() << std::endl;
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
			std::cerr << "ERROR: read M02: Error: " << status << std::endl;
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