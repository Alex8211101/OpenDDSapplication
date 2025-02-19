#include "DataReaderListenerImpl.h"
#include "S03_TransferFileTypeSupportC.h"
#include "S03_TransferFileTypeSupportImpl.h"
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

	try {
		S03_TransferFile::FileMessageDataReader_var reader_i = S03_TransferFile::FileMessageDataReader::_narrow(reader);
		if (!reader_i) {
			std::cerr << "read: _narrow failed." << std::endl;
			return;
		}
		S03_TransferFile::FileMessage S03_TransferFile_pos;
		DDS::SampleInfo si;
		DDS::ReturnCode_t status = reader_i->take_next_sample(S03_TransferFile_pos, si);
		if (status == DDS::RETCODE_OK) {
			std::cout << "SampleInfo.sample_rank = " << si.sample_rank << std::endl;
			std::cout << "SampleInfo.instance_state = " << si.instance_state << std::endl;
			if (si.valid_data/*&&S03_TransferFile_pos.PublisherName.in()!=host*/)
			{
				time_t nowTime;
				time(&nowTime);
				struct timeb tb;
				ftime(&tb);
				std::cout << std::endl << "[S03]发送者消息编号：" << S03_TransferFile_pos.FileMessageID << std::endl
					<< "[S03]发送者毫秒级计时：" << S03_TransferFile_pos.ClockTime << std::endl;
					cout << "[S03]发送者主机名：" << S03_TransferFile_pos.PublisherName << std::endl;
					cout<< "==================================================" << std::endl
					<<"对方尝试向您发送："<< S03_TransferFile_pos.PublishMessage<< std::endl
					<< "==================================================" << std::endl
					<< "文件长度为:" << S03_TransferFile_pos.FileLength <<"字节"<<std::endl
					<< "[S03]发送者发送时间：" << S03_TransferFile_pos.MTime 
					<< "[S03]本地接收时间：" << ctime(&nowTime) 
					<< "[S03]本地消息接收毫秒级计时：" << clock() << std::endl;
					//<<"Include:" << S03_TransferFile_pos.CatchedFile << std::endl
				if (S03_TransferFile_pos.FileLength > 0)
				{
					/*char *st;
					std::string ed;
					st = (char*)malloc(S03_TransferFile_pos.FileLength * sizeof(char));
				    ed=S03_TransferFile_pos.CatchedFile;
					ed.copy(st, ed.length()+1, 0);*/
					//string finals;
					//finals.append(S03_TransferFile_pos.CatchedFile.in(), S03_TransferFile_pos.FileLength);
					FILE* writep;
					writep = fopen(S03_TransferFile_pos.PublishMessage, "wb+");
					char *FilePtr;
					FilePtr=(char*)malloc(S03_TransferFile_pos.FileLength * sizeof(char));
					memcpy(FilePtr, &S03_TransferFile_pos.OFile[0], S03_TransferFile_pos.FileLength);
					fwrite(FilePtr, sizeof(char), S03_TransferFile_pos.FileLength, writep);
					fclose(writep);
					std::cout<< "[S03]本地文件传输执行完成毫秒级计时：" << clock() << std::endl;
				}
			}
			/*else if (si.valid_data&&S03_TransferFile_pos.PublisherName.in() == host)
			{

			}*/
			else if (si.instance_state == DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE)
			{
				std::cout << "instance is disS03_TransferFile_posed" << std::endl;
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
			std::cerr << "ERROR: read FileMessage: Error: " << status << std::endl;
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