#pragma once
#include "Protocol.h"

namespace FileSystem
{
	class CMarkup;
}

namespace Protocol{

class CH104:
	public CProtocol
{
public:
	CH104(boost::asio::io_service & io_service);
	~CH104(void);

	virtual int LoadXmlCfg(std::string filename);
	virtual void SaveXmlCfg(std::string filename);

protected:
	virtual int CheckFrameHead(unsigned char * buf,size_t & exceptedBytes);
	virtual int CheckFrameTail(unsigned char * buf,size_t exceptedBytes);
	virtual int ParseFrameBody(unsigned char * buf,size_t exceptedBytes);

	virtual int AssembleFrameHead(size_t bufIndex, unsigned char * buf, CCmd & cmd);
	virtual int AssembleFrameBody(size_t bufIndex, unsigned char * buf, CCmd & cmd);
	virtual int AssembleFrameTail(size_t bufBegin, size_t bufIndex, unsigned char * buf, CCmd & cmd);

	virtual int InitProtocol();
	virtual void UninitProtocol();

	virtual int QueryUnAliveCommPoint(share_commpoint_ptr point);

private:
	void InitObjectIndex();
	bool CheckIFrameRecvCounter(unsigned short sendVal);
	bool CheckIFrameSendCounter(unsigned short recvVal);
	void ClearIFrameCounter();

	bool CheckCounterKU();
	bool CheckCounterKI();
	bool CheckCounterWI();
	void ClearCounterKU();
	void ClearCounterKI();
	void ClearCounterWI();
	void IGramFrameSend();
	void UGramFrameSend();
	void IGramFrameRecv();

	void InitDefaultStartAddr();
	void InitDefaultFrameElem();
	void InitFrameLocation(size_t FrameHead);
	void InitDefaultTimeOut();
	void InitDefaultTimer(boost::asio::io_service & io_service);
	void InitFrameLength();

	//para api
	int setSYX_START_ADDR(size_t val);
	int setDYX_START_ADDR(size_t val);
	int setYC_START_ADDR(size_t val);
	int setSYK_START_ADDR(size_t val);
	int setDYK_START_ADDR(size_t val);
	int setYM_START_ADDR(size_t val);
	int setHIS_START_ADDR(size_t val);

	int setFrameLenLength(unsigned short val);
	int setIGramCounterLength(unsigned short val);
	int setFrameTypeLength(unsigned short val);
	int setInfoNumLength(unsigned short val);
	int setTransReasonLength(unsigned short val);
	int setAsduAddrLength(unsigned short val);
	int setInfoAddrLength(unsigned short val);

	int setTimeOutQueryUnActivePoint(unsigned short val);
	int setTimeOutRequrieLink(unsigned short val);
	int setTimeOutAnyFrameRecv(unsigned short val);
	int setTimeOutIGramFrameRecv(unsigned short val);
	int setTimeOutCallAllData(unsigned short val);
	int setTimeOutCallAllDD(unsigned short val);
	int setTimeOutSynTime(unsigned short val);
	int setTimeOutHeartFrame(unsigned short val);
	int setTimeOutYkSel(unsigned short val);
	int setTimeOutYkExe(unsigned short val);
	int setTimeOutYkCancel(unsigned short val);
	int setTimeOutCallPara(unsigned short val);
	int setTimeOutSetPara(unsigned short val);

	//timer
	void handle_timerRequireLink(const boost::system::error_code& error,share_commpoint_ptr point);
	void handle_timerCallAllData(const boost::system::error_code& error,share_commpoint_ptr point);
	void handle_timerCallAllDD(const boost::system::error_code& error,share_commpoint_ptr point);
	void handle_timerSynTime(const boost::system::error_code& error,share_commpoint_ptr point);
	void handle_timerHeartFrame(const boost::system::error_code& error,share_commpoint_ptr point);
	void handle_timerYkSel(const boost::system::error_code& error,share_commpoint_ptr point,size_t yk_no);
	void handle_timerYkExe(const boost::system::error_code& error,share_commpoint_ptr point,size_t yk_no);
	void handle_timerYkCancel(const boost::system::error_code& error,share_commpoint_ptr point,size_t yk_no);
	void handle_timerCallPara(const boost::system::error_code& error,share_commpoint_ptr point);
	void handle_timerSetPara(const boost::system::error_code& error,share_commpoint_ptr point);
	void handle_timerAnyFrameRecv(const boost::system::error_code& error);
	void handle_timerIGramFrameRecv(const boost::system::error_code& error,share_commpoint_ptr point);

	void ResetTimerRequireLink(share_commpoint_ptr point,bool bContinue = true, unsigned short val = 0);
	void ResetTimerCallAllData(share_commpoint_ptr point,bool bContinue = true,unsigned short val = 0);
	void ResetTimerCallAllDD(share_commpoint_ptr point,bool bContinue = true,unsigned short val = 0);
	void ResetTimerSynTime(share_commpoint_ptr point,bool bContinue = true,unsigned short val = 0);
	void ResetTimerHeartFrame(share_commpoint_ptr point,bool bContinue = true,unsigned short val = 0);
	void ResetTimerAnyFrameRecv(bool bContinue = true,unsigned short val = 0);
	void ResetTimerIGramFrameRecv(share_commpoint_ptr point,bool bContinue = true,unsigned short val = 0);
	void ResetTimerYkSel(share_commpoint_ptr point,size_t yk_no,bool bContinue = false,unsigned short val = 0);
	void ResetTimerYkExe(share_commpoint_ptr point,size_t yk_no,bool bContinue = false,unsigned short val = 0);
	void ResetTimerYkCancel(share_commpoint_ptr point,size_t yk_no,bool bContinue = false,unsigned short val = 0);
	void ResetTimerCallPara(share_commpoint_ptr point,bool bContinue = false,unsigned short val = 0);
	void ResetTimerSetPara(share_commpoint_ptr point,bool bContinue = false,unsigned short val = 0);
	
	//send frame assemble
	int AssembleSGram(size_t bufIndex, unsigned char * buf);
	int AssembleStartDTAct(size_t bufIndex, unsigned char * buf);
	int AssembleStartDTCon(size_t bufIndex, unsigned char * buf);
	int AssembleStopDTAct(size_t bufIndex, unsigned char * buf);
	int AssembleStopDTCon(size_t bufIndex, unsigned char * buf);
	int AssembleTestFRAct(size_t bufIndex, unsigned char * buf);
	int AssembleTestFRCon(size_t bufIndex, unsigned char * buf);
	int AssembleCallAllData(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr);
	int AssembleCallAllDD(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr);
	int AssembleSynTime(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr, boost::posix_time::ptime time);
	int AssembleDoubleYKSel(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,unsigned short yk_no, unsigned char yk_code,size_t trans_reason);
	int AssembleDoubleYKExe(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,unsigned short yk_no, unsigned char yk_code,size_t trans_reason);
	int AssembleDoubleYKCancel(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,unsigned short yk_no,unsigned char yk_code,size_t trans_reason);
	int AssembleSingleYKSel(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,unsigned short yk_no, unsigned char yk_code,size_t trans_reason);
	int AssembleSingleYKExe(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,unsigned short yk_no, unsigned char yk_code,size_t trans_reason);
	int AssembleSingleYKCancel(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,unsigned short yk_no,unsigned char yk_code,size_t trans_reason);
	int AssembleCallPara(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,int secondaryIndex);
	int AssembleSetPara(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,int secondaryIndex);
	int AssembleCallExtendRTUInfo(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr);
	int AssembleCallHistoryData(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,boost::posix_time::ptime time);
	int AssembleCallHistoryDatas(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,boost::posix_time::ptime startTime,boost::posix_time::ptime endTime);
	int AssembleCallFaultRecordData(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr);
	int AssembleCallYkRecordData(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr);
	int AssembleCallYxRecordData(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr);
	int AssembleCallJBPara(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,CCmd & cmd);
	int AssembleSendJBPara(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,CCmd & cmd);
	int AssembleActJBPara(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,CCmd & cmd);
	int AssembleDeactJBPara(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,CCmd & cmd);
	int AssembleSignalResetJBPara(size_t bufIndex, unsigned char * buf, share_terminal_ptr terminalPtr,CCmd & cmd);

	//recv frame parse
	int ParseFrame_S(unsigned char * buf);
	int ParseFrame_U(unsigned char * buf);
	int ParseFrame_I(unsigned char * buf);
	int ParseDoubleYKSelCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseDoubleYKExeCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseDoubleYKCancelCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseDoubleYKOverCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseSingleYKSelCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseSingleYKExeCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseSingleYKCancelCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseSingleYKOverCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllDataCallCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllDataCallOver(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllSingleYX(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllDoubleYX(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllYXByte(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseSingleCOS(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseDoubleCOS(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllYCData(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllYCDataWithValid(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllYCDataWithValidTE(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseYCCH(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseYCCHWithValid(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseYCCHWithValidTE(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseSynTimeCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseSingleSOE(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseDoubleSOE(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllYMCallCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllYMCallOver(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllYMData(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseEndInit(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseSetParaCon(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseSetParaErr(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseAllParaData(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseExtendRTUInfo(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseHistoryData(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseNoHistoryData(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseEndHistoryData(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseFaultRecordData(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseFaultRecordEnd(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseYkRecordData(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseYkRecordEnd(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseYxRecordData(unsigned char * buf, share_terminal_ptr terminalPtr);
	int ParseYxRecordEnd(unsigned char * buf, share_terminal_ptr terminalPtr);

	int ParseJBSoe(unsigned char * buf,share_terminal_ptr pristationPtr);
	int ParseCallJBParaCon(unsigned char * buf,share_terminal_ptr pristationPtr);
	int ParseSendJBParaCon(unsigned char * buf,share_terminal_ptr pristationPtr);
	int ParseActALLParaCon(unsigned char * buf,share_terminal_ptr pristationPtr);
	int ParseDeacALLtParaCon(unsigned char * buf,share_terminal_ptr pristationPtr);
	int ParseSignalResetCon(unsigned char * buf,share_terminal_ptr pristationPtr);

private:
	enum h104Para
	{
		DEFAULT_SUM_K = 16,                                     //104��Լ�з���12֡I����U����δ�յ�ȷ�ϣ��ж�Ϊ���ӳ���
		DEFAULT_SUM_W = 8,                                      //104��Լ��ÿ�յ�6֡I���ģ����Զ�ȷ��

		DEFAULT_SYX_START_ADDR = 0x0001,                        //Ĭ�ϵ���yx��ʼ��ַ
		DEFAULT_DYX_START_ADDR = 0x0001,                        //Ĭ��˫��yx��ʼ��ַ
		DEFAULT_YC_START_ADDR = 0x4001,                         //Ĭ��yc��ʼ��ַ
		DEFAULT_SYK_START_ADDR = 0x6001,                        //Ĭ�ϵ���yk��ʼ��ַ
		DEFAULT_DYK_START_ADDR = 0x6001,                        //Ĭ��˫��yk��ʼ��ַ
		DEFAULT_YM_START_ADDR = 0x6401,                         //Ĭ��ym��ʼ��ַ
		DEFAULT_HIS_START_ADDR = 0x0000,                        //Ĭ����ʷ������ʼ��ַ

		DEFAULT_FrameLenLength = 1,                             //Ĭ�ϱ��ĳ��ȱ�ʶ���ֽڳ���
		DEFAULT_IGramCounterLength = 2,
		DEFAULT_FrameTypeLength = 1,                            //Ĭ�ϱ������ͱ�ʶ���ֽڳ���
		DEFAULT_InfoNumLength = 1,                              //Ĭ����Ϣ����Ŀ��ʶ���ֽڳ���
		DEFAULT_TransReasonLength = 2,                          //Ĭ�ϴ���ԭ���ʶ���ֽڳ���
		DEFAULT_AsduAddrLength = 2,                             //Ĭ��װ�õ�ַ��ʶ���ֽڳ���
		DEFAULT_InfoAddrLength = 3,                             //Ĭ����Ϣ���ַ��ʶ���ֽڳ���

		DEFAULT_timeOutQueryUnActivePoint = 600,
		MIN_timeOutQueryUnActivePoint = 60,
		DEFAULT_timeOutRequireLink = 5,
		MIN_timeOutRequireLink = 1,
		DEFAULT_timeOutAnyFrameRecv = 150,
		DEFAULT_timeOutIGramFrameRecv = 10,
		DEFAULT_timeOutCallAllData = 600,
		MIN_timeOutCallAllData = 120,
		DEFAULT_timeOutCallAllDD = 900,
		MIN_timeOutCallAllDD = 180,
		DEFAULT_timeOutSynTime = 1800,
		MIN_timeOutSynTime = 300,
		DEFAULT_timeOutHeartFrame = 10,
		MIN_timeOutHeartFrame = 1,
		DEFAULT_timeOutYkSel = 25,
		DEFAULT_timeOutYkExe = 25,
		DEFAULT_timeOutYkCancel = 25,
		DEFAULT_timeOutCallPara = 10,
		DEFAULT_timeOutSetPara = 20
	};

	static size_t H104ObjectCounter_;

	unsigned short IFrameRecvCounter_;                  //�ձ������кż�����
	unsigned short IFrameSendCounter_;                  //���������кż�����

	unsigned short count_K_U_;                          //��������U��ʽ���ļ�����
	unsigned short count_K_I_;                          //��������I��ʽ���ļ�����
	unsigned short count_W_I_;                          //��������I��ʽ���ļ�����
	unsigned short H104_SUM_K_;                         //K�������Ļ�׼ֵ
	unsigned short H104_SUM_W_;                         //W�������Ļ�׼ֵ

	size_t SYX_START_ADDR_;                              //����yx��ʼ��ַ
	size_t DYX_START_ADDR_;                              //˫��yx��ʼ��ַ
	size_t YC_START_ADDR_;                               //yc��ʼ��ַ
	size_t SYK_START_ADDR_;                              //����yk��ʼ��ַ
	size_t DYK_START_ADDR_;                              //˫��yk��ʼ��ַ
	size_t YM_START_ADDR_;                               //ym��ʼ��ַ
	size_t HIS_START_ADDR_;                              //��ʷ������ʼ��ַ

	unsigned short FrameLenLength_;                              //���ĳ��ȱ�ʶ���ֽڳ���
	unsigned short IGramCounterLength_;
	unsigned short FrameTypeLength_;                             //�������ͱ�ʶ���ֽڳ���
	unsigned short InfoNumLength_;                               //��Ϣ����Ŀ��ʶ���ֽڳ���
	unsigned short TransReasonLength_;                           //����ԭ���ʶ���ֽڳ���
	unsigned short AsduAddrLength_;                              //װ�õ�ַ��ʶ���ֽڳ���
	unsigned short InfoAddrLength_;                              //��Ϣ���ַ��ʶ���ֽڳ���

	unsigned short FrameLenLocation_;                            //���ĳ��ȱ�ʶ���ֽڶ�λ
	unsigned short RecvCounterLocation_;
	unsigned short SendCounterLocation_;
	unsigned short FrameTypeLocation_;                           //�������ͱ�ʶ���ֽڶ�λ
	unsigned short InfoNumLocation_;                             //��Ϣ����Ŀ��ʶ���ֽڶ�λ
	unsigned short TransReasonLocation_;                         //����ԭ���ʶ���ֽڶ�λ
	unsigned short AsduAddrLocation_;                            //װ�õ�ַ��ʶ���ֽڶ�λ
	unsigned short InfoAddrLocation_;                            //��Ϣ���ַ��ʶ���ֽڶ�λ
	unsigned short DataLocation_;                                //���ݱ�ʶ���ֽڶ�λ
	
	unsigned short timeOutQueryUnActivePoint_;
	bool bUseTimeOutQueryUnActivePoint_;
	unsigned short timeOutRequireLink_;
	timerPtr timerRequireLink_;
	unsigned short timeOutAnyFrameRecv_;
	timerPtr timerAnyFrameRecv_;
	unsigned short timeOutIGramFrameRecv_;
	timerPtr timerIGramFrameRecv_;
	unsigned short timeOutCallAllData_;
	timerPtr timerCallAllData_;
	unsigned short timeOutCallAllDD_;
	timerPtr timerCallAllDD_;
	unsigned short timeOutSynTime_;
	timerPtr timerSynTime_;
	unsigned short timeOutHeartFrame_;
	timerPtr timerHeartFrame_;
	unsigned short timeOutYkSel_;
	timerPtr timerYkSel_;
	unsigned short timeOutYkExe_;
	timerPtr timerYkExe_;
	unsigned short timeOutYkCancel_;
	timerPtr timerYkCancel_;
	unsigned short timeOutCallPara_;
	timerPtr timerCallPara_;
	unsigned short timeOutSetPara_;
	timerPtr timerSetPara_;

	bool bCheckIFrameRecvCounter_;
	bool bCheckIFrameSendCounter_;
};

};//namespace Protocol