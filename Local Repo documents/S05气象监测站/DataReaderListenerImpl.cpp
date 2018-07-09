#include "DataReaderListenerImpl.h"
#include "YH03TypeSupportC.h"
#include "YH03TypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <ace/streams.h>
#include<time.h>
#include <sys/timeb.h>

void DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
{
	try {
		YH03::ObserveDataReader_var reader_i = YH03::ObserveDataReader::_narrow(reader);
		if (!reader_i) {
			std::cerr << "read: _narrow failed." << std::endl;
			return;
		}
		YH03::Observe YH03_Observe;
		DDS::SampleInfo si;
		DDS::ReturnCode_t status = reader_i->take_next_sample(YH03_Observe, si);
		if (status == DDS::RETCODE_OK) {
			
			std::cout << "���յ��۲�վ����" << std::endl;
			//std::cout << "SampleInfo.sample_rank = " << si.sample_rank << std::endl;
			//std::cout << "SampleInfo.instance_state = " << si.instance_state << std::endl;
			if (si.valid_data)
			{
				time_t nowTime;
				time(&nowTime);
				struct timeb tb;
				ftime(&tb);
				std::cout << std::endl << "[S05]��������Ϣ��ţ�" << YH03_Observe.YH03_Observe_ID << std::endl
					<< "[S05]�����ߺ��뼶��ʱ��" << YH03_Observe.ClockTime << std::endl;
				cout << "[S05]��������������" << YH03_Observe.YH03_Observe_name << std::endl;
				cout << "==================================================" << std::endl;
				std::cout << "  �۲�վ���ݱ�� = " << YH03_Observe.YH03_Observe_ID << std::endl
					<< "   �۲�վ���ƣ�" << YH03_Observe.YH03_Observe_name << std::endl
					<< "   �۲�PM2.5��" << YH03_Observe.YH03_Observe_pm2 << std::endl
					<< "   �۲��¶ȣ�" << YH03_Observe.Yh03_Observe_tem << std::endl;
				if (YH03_Observe.YH03_Observe_pm2 > 500)
				{
					cout << "+++++++++++++++++++++++" << endl;
					cout << "PM2.5�Ѿ�����500��ֵ��" << endl;
					cout << "PM2.5�Ѿ�����500��ֵ��" << endl;
					cout << "PM2.5�Ѿ�����500��ֵ��" << endl;
					cout << "+++++++++++++++++++++++" << endl;
				}
				if (YH03_Observe.Yh03_Observe_tem>35)
				{
					cout << "+++++++++++++++++++++++" << endl;
					cout << "������ɫԤ����" << endl;
					cout << "������ɫԤ����" << endl;
					cout << "������ɫԤ����" << endl;
					cout << "+++++++++++++++++++++++" << endl;
				}
				else if (YH03_Observe.Yh03_Observe_tem<-6)
				{
					cout << "+++++++++++++++++++++++" << endl;
					cout << "���º�����ɫԤ����" << endl;
					cout << "���º�����ɫԤ����" << endl;
					cout << "���º�����ɫԤ����" << endl;
					cout << "+++++++++++++++++++++++" << endl;
				}
				cout << "==================================================" << std::endl;
				cout << "[S05]�����߷���ʱ�䣺" << YH03_Observe.LocalTime;
				cout << "[S05]���ؽ���ʱ�䣺" << ctime(&nowTime);
				cout << "[S05]������Ϣ���պ��뼶��ʱ��" << clock() << std::endl;
				if (YH03_Observe.YH03_Observe_pm2>500 || YH03_Observe.Yh03_Observe_tem>35 || YH03_Observe.Yh03_Observe_tem<-6)
				{
					outf << endl;
					outf << "  �۲�վ���� = " << YH03_Observe.YH03_Observe_name << endl;
					outf << "  �۲�վ���ݱ�� = " << YH03_Observe.YH03_Observe_ID << endl;
					outf << "  �۲�PM2.5��" << YH03_Observe.YH03_Observe_pm2 << endl;
					outf << "   �۲��¶ȣ�" << YH03_Observe.Yh03_Observe_tem << endl;
					if (YH03_Observe.YH03_Observe_pm2 > 500)
					{
						outf << "PM2.5�Ѿ�����500��ֵ��" << endl;
					}
					if (YH03_Observe.Yh03_Observe_tem > 35)
					{
						outf << "������ɫԤ����" << endl;
					}
					else if (YH03_Observe.Yh03_Observe_tem < -6)
					{
						outf << "���º�����ɫԤ����" << endl;
					}
				}

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
			std::cerr << "ERROR: read Observe: Error: " << status << std::endl;
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