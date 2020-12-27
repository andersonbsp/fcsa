#ifndef FCSADAPTER_INTERFACE_FCSADAPTER_INTERFACES_DTO_H_
#define FCSADAPTER_INTERFACE_FCSADAPTER_INTERFACES_DTO_H_

namespace fcsa {
//#################################################################################################
//## COMMON BASE : START
//##
	/////////////////////////////////////////////////////////////////////////////////////////////
	// forward declaration - sub dto
	class IRequestItem;
	class IResponseApprovalItem;
	class IResponsePurchaseItem;
	class IResponseFlatRatePaymentInfo;
	class IPurchaseItem;
	class IPurchaseNo;
	//
	class ICouponItem;	
	class ICartItemInfo;
	class IRegisterItem;
	class IApprovalItem;
	class ICartItem;
	class IRequestNo;
	class IWishItemInfo;
	class ICashInventoryItems;
	class ICashInventoryItemsByBindAttribute;
	class IPackageItem;
	class IPackageItemByBindAttribute;
	class ILotteryItem;
	class ILotteryItemByBindAttribute;
	class IBonusItem;
	class IBonusItemByBindAttribute;
	class IPickupStandbyCashInventoryItem;
	class ISTItemProperty;
	//
	class IPStrA;
	class IJewelBalanceItem;
	class IWShopRequestPurchaseItem;
	class IWShopResponseApproval;
	class IWShopRequestOrderId;
	class IWShopInventoryItem;
	class IWShopPickUpItem;
	class IWShopResponseOrderStatus;
	/////////////////////////////////////////////////////////////////////////////////////////////
	// utility
	typedef const wchar_t* PStr;

	// ��� �������̽��� ����ϴ� ���� �������̽�
	class IObject
	{
	public:
		IObject(){}
		virtual ~IObject(){}
	public:
		virtual void release()				=0;	// �ڿ����� �ʼ�
		virtual const wchar_t* toString()	=0;	// ������
	};
	
	// DTO �� sub DTO �� ��� �迭 Ŭ����
	template<typename T>
	class IArrayPtr
	{
	public:
		IArrayPtr(){}
		virtual ~IArrayPtr(){}

		// sub DTO �߰� �� ����
		// sub DTO�� �ڽ��� ������ DTO�� ���� �����ֱ⸦ ����.
		// ��, DTO�� release() �ɶ� IArrayPtr�� ��ϵǾ��ִ� DTO�鵵 release()��
		virtual T add()			=0;		
		virtual INT32 size()	=0;		// ���� ������
		virtual bool empty()	=0;		// ����ִ��� ����
		virtual T at(INT32 i)	=0;		// �ش� ��ġ ��ü ����(���� ��� NULL)
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Request, Response interface ����
	class IRequestResponseParent : public IObject
	{
	public:
		IRequestResponseParent()			{}
		virtual ~IRequestResponseParent()	{}

		virtual BYTE	reserved_character()			=0;	//[1]0xFF
	//	virtual void	reserved_character(BYTE var)	=0;
		virtual INT32	packet_length()					=0;	//[4]��ü Packet ���� (������� 5bytes ����)
	//	virtual void	packet_length(INT32 var)		=0;
		virtual BYTE	packet_type()					=0;	//[1]Packet ����
	//	virtual void	packet_type(BYTE var)			=0;
		virtual INT32	transaction_id()				=0;	//[4]Ŭ���̾�Ʈ���� �����ϴ� �ֹ���ȣ
		virtual void	transaction_id(INT32 var)		=0;	//sync ��Ž� �߿��� ��

		//[���]
		virtual void	clear(bool parent=true)			=0;	// ������ ��� �ʱ�ȭ. false�� �ٰ�� �θ� class�� ������ ����� �ʱ�ȭ ���� �ʴ´�.
	};

	class IRequestParent : public IRequestResponseParent
	{
	public:
		IRequestParent()			{}
		virtual ~IRequestParent()	{}
	
		virtual INT32	issue_transaction_id()		=0;	// ���� dto�� transaction_id ��߱�
	};

	class IResponseParent : public IRequestResponseParent
	{
	public:
		IResponseParent()			{}
		virtual ~IResponseParent()	{}

		virtual INT32	result_code()				=0;	//[4]���� ��� �� : fcsa::kRCSuccess �� ��� ����(fcs_constant.h ����)
		virtual void	result_code(INT32 var)		=0;
		virtual BYTE	condition_type()			=0;	//[1]FCS ���� ���� : fcsa::kCT_Running �� ��� ����(fcs_constant.h ����)
		virtual void	condition_type(BYTE var)	=0;

		// [���]
		// result_code(), condition_type() ���󿩺� üũ (fcs_constant.h ����)
		// resulce_code �� kRCSuccess �̰� condition_type �� kCT_Running �� ��� true ����
		virtual bool	isSuccess()					=0;
		// [���]
		// response�� Extension �׸� json ������ ����Ѵٰ� ǥ��Ǿ� ���� ��� �����
		// extension : Response �� extension() �׸�
		// key : json�� key��
		// default_value : json parsing�� ���� ���� ��� return ������ �ޱ� ���ϴ� ��
		virtual void	extension_string(PStr extension, PStr key, PStr default_value, wchar_t* return_value, size_t return_value_size) =0;
		virtual int		extension_int(PStr extension, PStr key, int default_value) =0;
		virtual double	extension_double(PStr extension, PStr key, double default_value) =0;
		virtual bool	extension_bool(PStr extension, PStr key, bool default_value) =0;
	};

//## COMMON BASE : END
//##
//#################################################################################################
//##
//#################################################################################################
//## COMMAN : START
//##
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Common Step 1: Initialize 
	class IRequestInitialize : public IRequestParent
	{
	public:
		IRequestInitialize()			{}
		virtual ~IRequestInitialize()	{}

		virtual PStr	service_code()						=0;	//[?]���� �ڵ�
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0;	//[4]�����ȣ
		virtual void	world_no(INT32 var)					=0;
		virtual INT32	client_keep_alive_period()			=0;	//[4]�������� �ð� (0���� �Ǵ� 0x7FFFFFFF�̸� �������� üũ�� ���� �ʴ´�.)
		virtual void	client_keep_alive_period(INT32 var)	=0;
	};

	class IResponseInitialize : public IResponseParent
	{
	public:
		IResponseInitialize()			{}
		virtual ~IResponseInitialize()	{}

		virtual PStr	service_code()			=0;	//[?]�����ڵ�
		virtual void	service_code(PStr var)	=0;
		virtual INT32	world_no()				=0;	//[4]�����ȣ
		virtual void	world_no(INT32 var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Common Step 2: Keep Alive
	class IRequestKeepAlive : public IRequestParent
	{
	public:
		IRequestKeepAlive()				{}
		virtual ~IRequestKeepAlive()	{}

		virtual INT64	caching_product_version()			=0;	//[8]��ǰ ����Ʈ ���� Hash Code ��
		virtual void	caching_product_version(INT64 var)	=0;
	};

	class IResponseKeepAlive : public IResponseParent
	{
	public:
		IResponseKeepAlive()			{}
		virtual ~IResponseKeepAlive()	{}
	};

//## COMMON : END
//##
//#################################################################################################
//##
//#################################################################################################
//## AUTHENTICATION & AUTHORIZATION : START
//##
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 1: Game Login : ���� �α���
	class IRequestGameLogin : public IRequestParent
	{
	public:
		IRequestGameLogin()				{}
		virtual ~IRequestGameLogin()	{}

		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	authentication_key()			=0;	//[?]����Ű
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseGameLogin : public IResponseParent
	{
	public:
		IResponseGameLogin()			{}
		virtual ~IResponseGameLogin()	{}

		virtual bool										is_flat_rate_user()					=0; //[1]�������� ����
		virtual void										is_flat_rate_user(bool var)			=0;
		virtual PStr										user_type()							=0; //[?]��������. (fcs_constant.h�� "Table 7 Authorization User Type" ����)
		virtual void										user_type(PStr var)					=0;
		virtual IArrayPtr<IResponseFlatRatePaymentInfo*>*	structure_array()					=0; //[?]Ȱ��ȭ�� ���׻�ǰ ����ü �迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 2: Game Logout : ���� �α׾ƿ�
	class IRequestGameLogout : public IRequestParent
	{
	public:
		IRequestGameLogout()			{}
		virtual ~IRequestGameLogout()	{}

		virtual INT32	user_no()			=0; //[4]����� ��ȣ
		virtual void	user_no(INT32 var)	=0;
		virtual PStr	client_ip()			=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)	=0;
	};

	class IResponseGameLogout : public IResponseParent
	{
	public:
		IResponseGameLogout()			{}
		virtual ~IResponseGameLogout()	{}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 3: Premium Service Expired Callback : �����̾� ���� �Ⱓ ����

	class IResponsePremiumServiceExpiredCallback : public IResponseParent
	{
	public:
		IResponsePremiumServiceExpiredCallback()			{}
		virtual ~IResponsePremiumServiceExpiredCallback()	{}

		virtual INT32	user_no()			=0; //[4]����� ��ȣ
		virtual void	user_no(INT32 var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 4: Force User Logout Callback : ���� �α׾ƿ�
	class IResponseForceUserLogoutCallback : public IResponseParent
	{
	public:
		IResponseForceUserLogoutCallback()			{}
		virtual ~IResponseForceUserLogoutCallback()	{}

		virtual INT32	user_no()				=0; //[4]����� ��ȣ
		virtual void	user_no(INT32 var)		=0;
		virtual PStr	description()			=0; //[?]����
		virtual void	description(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 5: Request Authentication Key : ����Ű ��û
	class IRequestAuthenticationKey : public IRequestParent
	{
	public:
		IRequestAuthenticationKey()				{}
		virtual ~IRequestAuthenticationKey()	{}

		virtual INT32		user_no()			=0; //[4]����� ��ȣ
		virtual void		user_no(INT32 var)	=0;
		virtual PStr		pii()				=0; //[?]PII
		virtual void		pii(PStr var)		=0;
		virtual PStr		client_ip()			=0; //[?]����� IP�ּ�
		virtual void		client_ip(PStr var)	=0;
	};

	class IResponseAuthenticationKey : public IResponseParent
	{
	public:
		IResponseAuthenticationKey()			{}
		virtual ~IResponseAuthenticationKey()	{}

		virtual PStr	authentication_key()			=0; //[?]����Ű ��
		virtual void	authentication_key(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 6: Validate Authentication Key : ����Ű ��ȿ�� �˻�
	class IRequestValidateAuthenticationKey : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKey()				{}
		virtual ~IRequestValidateAuthenticationKey()	{}

		virtual INT32	user_no()						=0; //[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	authentication_key()			=0; //[?]����Ű ��
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKey : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKey()			{}
		virtual ~IResponseValidateAuthenticationKey()	{}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 7: Validate Authentication Key with Extension : ����Ű ��ȿ�� �˻�
	class IRequestValidateAuthenticationKeyWithExtension : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKeyWithExtension()			{}
		virtual ~IRequestValidateAuthenticationKeyWithExtension()	{}

		virtual INT32	account_no()					=0; //[4]����� ��ȣ(�������� ���� ����� Account No)
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	authentication_key()			=0; //[?]����Ű ��
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKeyWithExtension : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKeyWithExtension()			{}
		virtual ~IResponseValidateAuthenticationKeyWithExtension()	{}

		virtual INT32	user_no()						=0; //[4]���հ��� User No
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]���հ��� User ID
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0; //[4]�α����� Account NO
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]�α����� Account ID
		virtual void	account_id(PStr var)			=0;
		virtual BYTE	channel_info()					=0;	//[1]ä�θ� ����
		virtual void	channel_info(BYTE var)			=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 8: Validate Authentication Key for Publisher : ����Ű ��ȿ�� �˻�
	class IRequestValidateAuthenticationKeyForPublisher : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKeyForPublisher()				{}
		virtual ~IRequestValidateAuthenticationKeyForPublisher()	{}

		virtual INT32	account_no()					=0; //[4]Publisher User No - ������� 0
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0;	//[?]Publisher User ID - ������� ""
		virtual void	account_id(PStr var)			=0;
		virtual PStr	authentication_key()			=0; //[?]����Ű ��
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKeyForPublisher : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKeyForPublisher()			{}
		virtual ~IResponseValidateAuthenticationKeyForPublisher()	{}

		virtual PStr	publisher_code()				=0;	//[?]Publisher�� ó�� ���� �� ����
		virtual void	publisher_code(PStr var)		=0;
		virtual INT32	user_no()						=0;	//[4]���հ���(GP ����) User No
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0;	//[?]���հ���(GP ����) User ID
		virtual void	user_id(PStr var)				=0;
		virtual INT32	publisher_no()					=0; //[4]�α����� Publisher No - ������� 0
		virtual void	publisher_no(INT32 var)			=0;
		virtual PStr	publisher_id()					=0;	//[?]�α����� Publisher ID - ������� ""
		virtual void	publisher_id(PStr var)			=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 9: Validate Authentication Key with Parent Safe : �θ� �Ƚ� ���� ����Ű ��ȿ�� �˻�
	class IRequestValidateAuthenticationKeyWithParentSafe : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKeyWithParentSafe()			{}
		virtual ~IRequestValidateAuthenticationKeyWithParentSafe()	{}

		virtual INT32	account_no()					=0;	//[4]������ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual BYTE	channel_info()					=0;	//[1]ä�θ� ����
		virtual void	channel_info(BYTE var)			=0;
		virtual PStr	authentication_key()			=0; //[?]����Ű ��
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKeyWithParentSafe : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKeyWithParentSafe()			{}
		virtual ~IResponseValidateAuthenticationKeyWithParentSafe()	{}

		virtual INT32	user_no()						=0; //[4]����: ������ȣ(�ֹε�Ϲ�ȣ ����), ONE: request ������ȣ ����(ONE ���� -> ONE ������ȣ, legacy ���� -> legacy ������ȣ)
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����: ������ ����, ONE: request ������ȣ ����(ONE ���� -> ONE ���� ��, legacy ���� -> legacy ���� ��)
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0; //[4]����: ������ȣ, ONE: ������ ����
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]����: ������, ONE: ������ ����
		virtual void	account_id(PStr var)			=0;
		virtual BYTE	channel_info()					=0; //[1]ä�θ� ����
		virtual void	channel_info(BYTE var)			=0;
		virtual SHORT	age()							=0; //[2]���� ����
		virtual void	age(SHORT var)					=0;
		virtual INT32	remain_time()					=0; //[4]���� �ð�(��)
		virtual void	remain_time(INT32 var)			=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 10: Validate Authentication Key for R2 : ���� R2 �� ����Ű ��ȿ�� �˻�
	class IRequestValidateAuthenticationKeyForR2 : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKeyForR2()			{}
		virtual ~IRequestValidateAuthenticationKeyForR2()	{}

		virtual INT32	account_no()					=0;	//[4]������ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	authentication_key()			=0; //[?]����Ű ��
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKeyForR2 : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKeyForR2()			{}
		virtual ~IResponseValidateAuthenticationKeyForR2()	{}

		virtual INT32	user_no()						=0; //[4]����: ������ȣ(�ֹε�Ϲ�ȣ ����), ONE: request ������ȣ ����(ONE ���� -> ONE ������ȣ, legacy ���� -> legacy ������ȣ)
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����: ������ ����, ONE: request ������ȣ ����(ONE ���� -> ONE ���� ��, legacy ���� -> legacy ���� ��)
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0; //[4]����: ������ȣ, ONE: ������ ����
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]����: ������, ONE: ������ ����
		virtual void	account_id(PStr var)			=0;
		virtual BYTE	account_type()					=0; //[1]����: R2 ���� Ÿ��
		virtual void	account_type(BYTE var)			=0;
		virtual BYTE	block_state()					=0; //[1]����: ��� ���� ����
		virtual void	block_state(BYTE var)			=0;
		virtual INT32	pcbang_index()					=0; //[4]����: PC�� �ε���
		virtual void	pcbang_index(INT32 var)			=0;
		virtual PStr	phone_auth()					=0; //[?]����: �� ���� Ű
		virtual void	phone_auth(PStr var)			=0;
		virtual INT32	is_phone_auth()					=0; //[4]����: �� ���� ����
		virtual void	is_phone_auth(INT32 var)		=0;
		virtual PStr	auth_ip()						=0; //[?]����: IP
		virtual void	auth_ip(PStr var)				=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 11: Validate Authentication Key with User Info : ����Ű ��ȿ�� �˻� (���� ���� Ȯ��)
	class IRequestValidateAuthenticationKeyWithUserInfo : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKeyWithUserInfo()				{}
		virtual ~IRequestValidateAuthenticationKeyWithUserInfo()	{}

		virtual PStr	callback_attribute()			=0; //[?]�������� ���޵� �ݹ� ������
		virtual void	callback_attribute(PStr var)	=0;
		virtual INT32	account_no()					=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	authentication_key()			=0; //[?]����Ű ��
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	extension()						=0; //[?]�߰� Ȯ�� ��Ҹ� ���� �ʵ�
		virtual void	extension(PStr var)				=0;
		virtual PStr	client_ip()						=0; //[?]����� IP �ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKeyWithUserInfo : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKeyWithUserInfo()			{}
		virtual ~IResponseValidateAuthenticationKeyWithUserInfo()	{}

		virtual PStr	callback_attribute()			=0; //[?]�������� ���޵� �ݹ� ������
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	provider_code()					=0; //[?]���ι��̴� �ڵ�
		virtual void	provider_code(PStr var)			=0;
		virtual INT32	user_no()						=0; //[4]����: ������ȣ(�ֹε�Ϲ�ȣ ����), ONE: request ������ȣ ����(ONE ���� -> ONE ������ȣ, legacy ���� -> legacy ������ȣ)
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����: ������ ����, ONE: request ������ȣ ����(ONE ���� -> ONE ���� ��, legacy ���� -> legacy ���� ��)
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0; //[4]����: ������ȣ, ONE: ������ ����
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]����: ������, ONE: ������ ����
		virtual void	account_id(PStr var)			=0;
		virtual PStr	extension()						=0; //[?]�߰� Ȯ�� ��Ҹ� ���� �ʵ�
		virtual void	extension(PStr var)				=0;
	};



	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 12: Account Login : ���� �α���
	class IRequestAccountLogin : public IRequestParent
	{
	public:
		IRequestAccountLogin()			{}
		virtual ~IRequestAccountLogin()	{}

		virtual PStr	account_id()			=0; //[?]WEBZEN AccountId
		virtual void	account_id(PStr var)	=0;
		virtual PStr	password()				=0; //[?]WEBZEN Account Password
		virtual void	password(PStr var)		=0;
		virtual PStr	pii()					=0; //[?]PII : ��->���ӷ�ó�� ���� ���޹޴� ����� PC ������
		virtual void	pii(PStr var)			=0;
		virtual PStr	client_ip()				=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)		=0;
	};

	class IResponseAccountLogin : public IResponseParent
	{
	public:
		IResponseAccountLogin()				{}
		virtual ~IResponseAccountLogin()	{}

		virtual INT32	user_no()							=0; //[4]����� ��ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual BYTE	failure_count()						=0; //[1]10�а� �α��� ����Ƚ��
		virtual void	failure_count(BYTE var)				=0;
		virtual PStr	user_type()							=0; //[?]�������� (fcs_constant.h "Table 7 Authorization User Type" ����)
		virtual void	user_type(PStr var)					=0;
		virtual PStr	user_status()						=0; //[?]�������� (fcs_constant.h "Table 8 Authorization User Status" ����)
		virtual void	user_status(PStr var)				=0;
		virtual PStr	security_provider_type()			=0; //[?]�������� (fcs_constant.h "Table 9 Authorization Security Provider Type" ����)
		virtual void	security_provider_type(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 13: Account Logout : ���� �α׾ƿ�
	class IRequestAccountLogout : public IRequestParent
	{
	public:
		IRequestAccountLogout()				{}
		virtual ~IRequestAccountLogout()	{}

		virtual INT32	user_no()			=0; //[4]����� ��ȣ
		virtual void	user_no(INT32 var)	=0;
		virtual PStr	client_ip()			=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)	=0;
	};

	class IResponseAccountLogout : public IResponseParent
	{
	public:
		IResponseAccountLogout()			{}
		virtual ~IResponseAccountLogout()	{}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 14: Set Account State : ������ ������ �α���/�α׾ƿ� ���� ��ȣ, IP, �ð�, �����α��� Ƚ�� ������Ʈ
	class IRequestSetAccountState : public IRequestParent
	{
	public:
		IRequestSetAccountState()			{}
		virtual ~IRequestSetAccountState()	{}

		virtual INT32	account_no()				=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)		=0;
		virtual PStr	game_code()					=0;	//[?]���� �ڵ�
		virtual void	game_code(PStr var)			=0;
		virtual INT32	server_id()					=0; //[4]���� ��ȣ
		virtual void	server_id(INT32 var)		=0;
		virtual INT32	connect_state()				=0; //[4]0: �α���, 1: �α׾ƿ�
		virtual void	connect_state(INT32 var)	=0;
		virtual PStr	client_ip()					=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)			=0;
	};

	class IResponseSetAccountState : public IResponseParent
	{
	public:
		IResponseSetAccountState()			{}
		virtual ~IResponseSetAccountState()	{}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 15: Get PC Room GUID : IP�� ��PC�� ������ȣ ��ȯ
	class IRequestGetPCRoomGuid : public IRequestParent
	{
	public:
		IRequestGetPCRoomGuid()				{}
		virtual ~IRequestGetPCRoomGuid()	{}

		virtual PStr	client_ip()			=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)	=0;
	};

	class IResponseGetPCRoomGuid : public IResponseParent
	{
	public:
		IResponseGetPCRoomGuid()			{}
		virtual ~IResponseGetPCRoomGuid()	{}

		virtual INT32	pc_room_guid()			=0;	//[4]PC�� ������ȣ
		virtual void	pc_room_guid(INT32 var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 16: Check Phone Auth User : ��ȭ���� ���԰��� ���� Ȯ��
	class IRequestCheckPhoneAuthUser : public IRequestParent
	{
	public:
		IRequestCheckPhoneAuthUser()			{}
		virtual ~IRequestCheckPhoneAuthUser()	{}

		virtual INT32	account_no()			=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)	=0;
		virtual PStr	client_ip()				=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)		=0;
	};

	class IResponseCheckPhoneAuthUser : public IResponseParent
	{
	public:
		IResponseCheckPhoneAuthUser()			{}
		virtual ~IResponseCheckPhoneAuthUser()	{}

		virtual INT32	state()				=0;	//[4]0: �̰���, 1: ����
		virtual void	state(INT32 var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 17: Get User Info : ���� ��ȣ�� ����� ���� Ȯ��
	class IRequestGetUserInfo : public IRequestParent
	{
	public:
		IRequestGetUserInfo()			{}
		virtual ~IRequestGetUserInfo()	{}

		virtual INT32	account_no()			=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)	=0;
		virtual PStr	client_ip()				=0; //[?]����� IP�ּ�
		virtual void	client_ip(PStr var)		=0;
	};

	class IResponseGetUserInfo : public IResponseParent
	{
	public:
		IResponseGetUserInfo()			{}
		virtual ~IResponseGetUserInfo()	{}

		virtual INT32	user_no()				=0; //[4]���� ��ȣ
		virtual void	user_no(INT32 var)		=0;
		virtual PStr	account_id()			=0; //[?]���� ��
		virtual void	account_id(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 18: Get User Info With Extension : ������ȣ�� ����� ���� Ȯ��
	class IRequestGetUserInfoWithExtension : public IRequestParent
	{
	public:
		IRequestGetUserInfoWithExtension() {}
		virtual ~IRequestGetUserInfoWithExtension() {}

		virtual INT32	account_no() =0; //[4] ����� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	client_ip() =0; //[?] ����� IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseGetUserInfoWithExtension : public IResponseParent
	{
	public:
		IResponseGetUserInfoWithExtension() {}
		virtual ~IResponseGetUserInfoWithExtension() {}

		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ�
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
	};


//## AUTHENTICATION & AUTHORIZATION : END
//##
//#################################################################################################
//##
//#################################################################################################
//## Basic Billing : START
//##
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 1: Check Balance : �ܾ���ȸ
	class IRequestCheckBalance : public IRequestParent
	{
	public:
		IRequestCheckBalance()			{}
		virtual ~IRequestCheckBalance()	{}

		virtual INT32	user_no()			=0; //[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)	=0;
		virtual PStr	client_ip()			=0; //[?]����� IP �ּ�
		virtual void	client_ip(PStr var)	=0;
	};

	class IResponseCheckBalance : public IResponseParent
	{
	public:
		IResponseCheckBalance()				{}
		virtual ~IResponseCheckBalance()	{}

		virtual INT32	p_coin()				=0; // P Coin �ܾ�
		virtual void	p_coin(INT32 var)		=0;
		virtual INT32	c_coin()				=0; // C Coin �ܾ�
		virtual void	c_coin(INT32 var)		=0;
		virtual INT32	p_event_coin()			=0; // P Event Coin �ܾ�
		virtual void	p_event_coin(INT32 var)	=0;
		virtual INT32	c_event_coin()			=0; // C Event Coin �ܾ�
		virtual void	c_event_coin(INT32 var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 2: Item Purchase : ������ ����
	class IRequestItemPurchase : public IRequestParent
	{
	public:
		IRequestItemPurchase()			{}
		virtual ~IRequestItemPurchase()	{}

		virtual INT32						user_no()						=0; //[4]����� ��ȣ
		virtual void						user_no(INT32 var)				=0;
		virtual IArrayPtr<IRequestItem*>*	request_item()					=0; //[?]���ӿ��� �����Ϸ��� ������ ������ ����ü �迭
		virtual INT32						total_item_amount()				=0; //[4]�����Ϸ��� ������ �ݾ��� ��
		virtual void						total_item_amount(INT32 var)	=0;
		virtual PStr						item_order_id()					=0; //[?]���ӿ��� �����ϴ� �ֹ���ȣ(World No�� ����ũ ���� �ʿ�)
		virtual void						item_order_id(PStr var)			=0;
		virtual INT32						character_no()					=0; //[4]ĳ���� ��ȣ
		virtual void						character_no(INT32 var)			=0;
		virtual PStr						character_name()				=0; //[?]ĳ���� �̸�
		virtual void						character_name(PStr var)		=0;
		virtual INT32						game_level()					=0;	//[4]���ӷ���
		virtual void						game_level(INT32 var)			=0;
		virtual PStr						description()					=0; //[?]����
		virtual void						description(PStr var)			=0;
		virtual PStr						client_ip()						=0; //[?]Ŭ���̾�Ʈ ip�ּ�
		virtual void						client_ip(PStr var)				=0;
		virtual INT32						optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ���
		virtual void						optional_world_no(INT32 var)	=0;
	};
	
	class IResponseItemPurchase : public IResponseParent
	{
	public:
		IResponseItemPurchase()				{}
		virtual ~IResponseItemPurchase()	{}

		virtual PStr				item_order_id()							=0; // ���ӿ��� ������ ����ũ �ֹ���ȣ
		virtual void				item_order_id(PStr var)					=0;
		virtual IArrayPtr<IResponseApprovalItem*>*	response_item_array()	=0;	// ������ �������� ����ü �迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 3: Item Gift : ��ǰ ����
	class IRequestItemGift : public IRequestParent
	{
	public:
		IRequestItemGift()			{}
		virtual ~IRequestItemGift()	{}

		virtual INT32						user_no()							=0; //[4]����� ��ȣ
		virtual void						user_no(INT32 var)					=0;
		virtual IArrayPtr<IRequestItem*>*	request_item()						=0; //[?]���ӿ��� �����Ϸ��� ������ ������ ����ü �迭
		virtual INT32						total_item_amount()					=0; //[4]�����Ϸ��� ������ �ݾ��� ��
		virtual void						total_item_amount(INT32 var)		=0;
		virtual PStr						item_order_id()						=0; //[?]���ӿ��� �����ϴ� �ֹ���ȣ(World No�� ����ũ ���� �ʿ�)
		virtual void						item_order_id(PStr var)				=0;
		virtual INT32						character_no()						=0; //[4]ĳ���� ��ȣ
		virtual void						character_no(INT32 var)				=0;
		virtual PStr						character_name()					=0; //[?]ĳ���� �̸�
		virtual void						character_name(PStr var)			=0;
		virtual INT32						game_level()						=0; //[4]���ӷ���
		virtual void						game_level(INT32 var)				=0;
		virtual INT32						receive_world_no()					=0; //[4]���� �޴� ĳ���� ���� ��ȣ
		virtual void						receive_world_no(INT32 var)			=0;
		virtual INT32						receive_character_no()				=0; //[4]���� �޴� ĳ���� ��ȣ
		virtual void						receive_character_no(INT32 var)		=0;
		virtual PStr						receive_character_name()			=0; //[?]���� �޴� ĳ���� �̸�
		virtual void						receive_character_name(PStr var)	=0;
		virtual PStr						message()							=0; //[?]���� �޽���
		virtual void						message(PStr var)					=0;
		virtual PStr						description()						=0; //[?]����
		virtual void						description(PStr var)				=0;
		virtual PStr						client_ip()							=0; //[?]Ŭ���̾�Ʈ ip�ּ�
		virtual void						client_ip(PStr var)					=0;
		virtual INT32						optional_world_no()					=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ���
		virtual void						optional_world_no(INT32 var)		=0;
	};

	class IResponseItemGift : public IResponseParent
	{
	public:
		IResponseItemGift()				{}
		virtual ~IResponseItemGift()	{}

		virtual PStr								item_order_id()				=0; // ���ӿ��� ������ ����ũ �ֹ���ȣ
		virtual void								item_order_id(PStr var)		=0;
		virtual IArrayPtr<IResponseApprovalItem*>*	response_item_array()		=0; // ������ �������� ����ü �迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 4: Check Purchase : ���� Ȯ��
	class IRequestCheckPurchase : public IRequestParent
	{
	public:
		IRequestCheckPurchase()				{}
		virtual ~IRequestCheckPurchase()	{}

		virtual PStr	item_order_id()			=0; //[?]����/���� �� ����� �ֹ���ȣ
		virtual void	item_order_id(PStr var)	=0;
		virtual PStr	client_ip()				=0; //[?]Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var)		=0;
	};

	class IResponseCheckPurchase : public IResponseParent
	{
	public:
		IResponseCheckPurchase()			{}
		virtual ~IResponseCheckPurchase()	{}

		virtual PStr	item_order_id()								=0; //[?]���ӿ��� ������ ����ũ �ֹ���ȣ
		virtual void	item_order_id(PStr var)						=0;
		virtual IArrayPtr<IPurchaseItem*>*	response_item_array()	=0; //[?]������ �������� ����ü �迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 5: Cancel Purchase : ���� ���
	class IRequestCancelPurchase : public IRequestParent
	{
	public:
		IRequestCancelPurchase()			{}
		virtual ~IRequestCancelPurchase()	{}

		virtual PStr	item_order_id()				=0; //[?]����/���� �� ����� �ֹ���ȣ
		virtual void	item_order_id(PStr var)		=0;
		virtual INT32	purchase_no()				=0; //[4]���Ž��� ��ȣ
		virtual void	purchase_no(INT32 var)		=0;
		virtual PStr	description()				=0; //[?]����
		virtual void	description(PStr var)		=0;
		virtual PStr	client_ip()					=0; //[?]Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var)			=0;
	};

	class IResponseCancelPurchase : public IResponseParent
	{
	public:
		IResponseCancelPurchase()			{}
		virtual ~IResponseCancelPurchase()	{}

		virtual PStr		item_order_id()			=0; //[?]���ӿ��� ������ ����ũ �ֹ���ȣ
		virtual void		item_order_id(PStr var)	=0;
		virtual INT32		purchase_no()			=0; //[4]�ֹ���ȣ
		virtual void		purchase_no(INT32 var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 6: Cancel Purchase by Order Id : �ֹ���ȣ�� �̿��ؼ� ��ü ���� ���
	class IRequestCancelPurchaseByOrderId : public IRequestParent
	{
	public:
		IRequestCancelPurchaseByOrderId()			{}
		virtual ~IRequestCancelPurchaseByOrderId()	{}

		virtual PStr	item_order_id()			=0; //[?]���ӿ��� ������ ����ũ �ֹ���ȣ
		virtual void	item_order_id(PStr var)	=0;
		virtual PStr	description()			=0; //[?]����
		virtual void	description(PStr var)	=0;
		virtual PStr	client_ip()				=0; //[?]Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var)		=0;
	};

	class IResponseCancelPurchaseByOrderId : public IResponseParent
	{
	public:
		IResponseCancelPurchaseByOrderId()			{}
		virtual ~IResponseCancelPurchaseByOrderId()	{}

		virtual PStr item_order_id()			=0; // ���ӿ��� ������ ����ũ �ֹ���ȣ
		virtual void item_order_id(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 7: Confirm Purchase by Order Id : �ֹ���ȣ�� �̿��ؼ� ��ü ���� ����
	//
	// �� 3�� ���� Confirm ���� ������ �ڵ� ��� (3���� FCS ���� ���� ����)
	// ��������� Confirm Ȥ�� Cancel ȣ�� �ǰ�. (�ڵ� ��Ҵ� ���� �������� ��ϵ�)
	class IRequestConfirmPurchaseByOrderId : public IRequestParent
	{
	public:
		IRequestConfirmPurchaseByOrderId()			{}
		virtual ~IRequestConfirmPurchaseByOrderId()	{}

		virtual PStr	item_order_id()					=0; //[?]�ֹ�/���� �� ����ߴ� �ֹ���ȣ
		virtual void	item_order_id(PStr var)			=0;
		virtual PStr	description()					=0; //[?]����
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ���
		virtual void	optional_world_no(INT32 var)	=0;
	};

	class IResponseConfirmPurchaseByOrderId : public IResponseParent
	{
	public:
		IResponseConfirmPurchaseByOrderId()				{}
		virtual ~IResponseConfirmPurchaseByOrderId()	{}

		virtual PStr	item_order_id()				=0; // ���ӿ��� ������ ����ũ �ֹ���ȣ
		virtual void	item_order_id(PStr var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 8: Purchase List : ���ų��� ��ȸ
	class IRequestPurchaseList : public IRequestParent
	{
	public:
		IRequestPurchaseList()			{}
		virtual ~IRequestPurchaseList()	{}

		virtual INT32	user_no()					=0; //[4]����� ��ȣ
		virtual void	user_no(INT32 var)			=0;
		virtual INT64	begin_datetime()			=0; //[8]��ȸ ������	: FILETIME : C#���� DateTime.Ticks ��
		virtual void	begin_datetime(INT64 var)	=0;
		virtual INT64	end_datetime()				=0; //[8]��ȸ ������	: FILETIME
		virtual void	end_datetime(INT64 var)		=0;
		virtual INT32	page_index()				=0; //[4]������ ��ȣ
		virtual void	page_index(INT32 var)		=0;
		virtual INT32	row_per_page()				=0; //[4]�������� ������ ����
		virtual void	row_per_page(INT32 var)		=0;
		virtual PStr	client_ip()					=0; //[?]Ŭ���̾�Ʈ IP �ּ�
		virtual void	client_ip(PStr var)			=0;
	};

	class IResponsePurchaseList : public IResponseParent
	{
	public:
		IResponsePurchaseList()				{}
		virtual ~IResponsePurchaseList()	{}

		virtual INT32	total_row_count()									=0; //[4]��ü ������ ��
		virtual void	total_row_count(INT32 var)							=0;
		virtual IArrayPtr<IResponsePurchaseItem*>*	purchase_item_array()	=0;	//[?]���� ���� ����ü �迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 9: Exchange WCoin : WCoin�� ���� ������ ���Ǵ� ����Ʈ�� ��ȯ
	class IRequestExchangeWCoin : public IRequestParent
	{
	public:
		IRequestExchangeWCoin()				{}
		virtual ~IRequestExchangeWCoin()	{}

		virtual INT32	user_no()							=0; //[4]����� ��ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	order_id()							=0; //[?]��ȯ �ֹ� ��ȣ (���ӿ��� �����Ͽ� ����)
		virtual void	order_id(PStr var)					=0;
		virtual INT32	exchange_wcoin_amount()				=0; //[4]ȯ���� WCoin �ݾ�
		virtual void	exchange_wcoin_amount(INT32 var)	=0;
		virtual PStr	description()						=0; //[?]����
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0; //[?]Ŭ���̾�Ʈ IP �ּ�
		virtual void	client_ip(PStr var)					=0;
	};

	class IResponseExchangeWCoin : public IResponseParent
	{
	public:
		IResponseExchangeWCoin()			{}
		virtual ~IResponseExchangeWCoin()	{}

		virtual PStr	order_id()							=0; //[?]���ӿ��� ������ ��ȯ �ֹ� ��ȣ
		virtual void	order_id(PStr var)					=0;
		virtual INT32	used_payed_amount()					=0;	//[4]������ WCoin �ݾ�
		virtual void	used_payed_amount(INT32 val)		=0;
		virtual INT32	used_bonus_amount()					=0;	//[4]������ ���ʽ� WCoin �ݾ�
		virtual void	used_bonus_amount(INT32 val)		=0;
		virtual INT32	purchase_no()						=0; //[4]���� ���� ��ȣ
		virtual void	purchase_no(INT32 var)				=0;
	};
//## Basic Billing : END
//#################################################################################################
//##
//#################################################################################################
//## WShop Billing : START
//##
	// WShop Billing Step 1 : WShop Check Balance : �ܾ���ȸ
	class IRequestWShopCheckBalance : public IRequestParent
	{
	public:
		IRequestWShopCheckBalance() {}
		virtual ~IRequestWShopCheckBalance() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ� (Get User Info With Ext���� ���� ���� �״�� ����)
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] ���ӿ��� �����ϴ� ���� Ű
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ (�� �� ���ų� �Ǵ� ����� ��� 0���� ��)
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] ĳ���� ���̵� (�� �� ���� ��� �� ���ڿ�)
		virtual void	character_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] ����� IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopCheckBalance : public IResponseParent
	{
	public:
		IResponseWShopCheckBalance() {}
		virtual ~IResponseWShopCheckBalance() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual INT64	coin() =0; //[8] ���� WCoin �ܾ�
		virtual void	coin(INT64 var) = 0;
		virtual IArrayPtr<IJewelBalanceItem*>* jewel_balance_item_array() =0; //[?] 2�� ȭ�� �ܾ� ������ �迭
	};
	// WShop Billing Step 2 : WShopPurchase : �� ������ ����
	class IRequestWShopPurchase : public IRequestParent
	{
	public:
		IRequestWShopPurchase() {}
		virtual ~IRequestWShopPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ�
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] ���ӿ��� �����ϴ� ���� Ű
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] ĳ���� ���̵�
		virtual void	character_id(PStr var) = 0;
		virtual INT32	game_level() =0; //[4] ���� ���� (������ ���  -1) : optional
		virtual void	game_level(INT32 var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
		virtual IArrayPtr<IWShopRequestPurchaseItem*>* request_purchase_item_array() =0; //[?] ��û ���� ������ �迭
	};
	class IResponseWShopPurchase : public IResponseParent
	{
	public:
		IResponseWShopPurchase() {}
		virtual ~IResponseWShopPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual IArrayPtr<IWShopResponseApproval*>* purchase_item_array() =0; //[?] ������ ����ü �迭
		virtual IArrayPtr<IJewelBalanceItem*>* jewel_balance_item_array() =0; //[?]2�� ȭ�� �ܾ� �迭 (��� ���� ���� ������ ���� �� ������Ʈ�� �ܾ��� ��ȯ�Ѵ�.)
	};

	// WShop Billing Step 3 : WShopCheckPurchase : �� ������ ���� Ȯ��
	class IRequestWShopCheckPurchase : public IRequestParent
	{
	public:
		IRequestWShopCheckPurchase() {}
		virtual ~IRequestWShopCheckPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
		virtual IArrayPtr<IWShopRequestOrderId*>* request_order_id_array() =0; //[?] ��û ���� ������ �迭
	};
	class IResponseWShopCheckPurchase : public IResponseParent
	{
	public:
		IResponseWShopCheckPurchase() {}
		virtual ~IResponseWShopCheckPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual IArrayPtr<IWShopResponseOrderStatus*>* response_order_status_array() = 0; //[?] �ֹ� �� ���� �迭
	};
	// WShop Billing Step 4 : WShopCancelPurchase : �� ������ ���� ���
	class IRequestWShopCancelPurchase : public IRequestParent
	{
	public:
		IRequestWShopCancelPurchase() {}
		virtual ~IRequestWShopCancelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
		virtual IArrayPtr<IWShopRequestOrderId*>* request_cancel_purchase_item_array() =0; //[?] ���� ��� ������ �迭
	};
	class IResponseWShopCancelPurchase : public IResponseParent
	{
	public:
		IResponseWShopCancelPurchase() {}
		virtual ~IResponseWShopCancelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
	};
	// WShop Billing Step 5 : WShopConfirmPurchase : �� ������ ���� ����
		class IRequestWShopConfirmPurchase : public IRequestParent
	{
	public:
		IRequestWShopConfirmPurchase() {}
		virtual ~IRequestWShopConfirmPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
		virtual IArrayPtr<IWShopRequestOrderId*>* request_order_id_array() =0; //[?] ��û ���� ������ �迭
	};
	class IResponseWShopConfirmPurchase : public IResponseParent
	{
	public:
		IResponseWShopConfirmPurchase() {}
		virtual ~IResponseWShopConfirmPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
	};
// WShop Billing Step 6 : WShopGift : �� ������ ����
	class IRequestWShopGift : public IRequestParent
	{
	public:
		IRequestWShopGift() {}
		virtual ~IRequestWShopGift() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ�
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] ���ӿ��� �����ϴ� ���� Ű
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] ĳ���� ���̵�
		virtual void	character_id(PStr var) = 0;
		virtual INT32	game_level() =0; //[4] ���ӷ��� (������ ���  -1) : optional
		virtual void	game_level(INT32 var) = 0;
		virtual INT32	item_sale_no() =0; //[4] ������ �Ǹ� ��ȣ
		virtual void	item_sale_no(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT32	purchase_price() =0; //[4] ���� �ݾ� (���η� �ִ°��� ���� ����� �ݾ�)
		virtual void	purchase_price(INT32 var) = 0;
		virtual SHORT	order_quantity() =0; //[2] �ֹ� ����
		virtual void	order_quantity(SHORT var) = 0;
		virtual PStr	attribute0() =0; //[?] �Ӽ� (Ŭ����� Property0) : optional
		virtual void	attribute0(PStr var) = 0;
		virtual PStr	attribute1() =0; //[?] �Ӽ� (Ŭ����� Property1) : optional
		virtual void	attribute1(PStr var) = 0;
		virtual PStr	attribute2() =0; //[?] �Ӽ� (Ŭ����� Property2) : optional
		virtual void	attribute2(PStr var) = 0;
		virtual PStr	attribute3() =0; //[?] �Ӽ� (Ŭ����� Property3) : optional
		virtual void	attribute3(PStr var) = 0;
		virtual PStr	attribute4() =0; //[?] �Ӽ� (Ŭ����� Property4) : optional
		virtual void	attribute4(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual INT32	receive_user_account_no() =0; //[4] ���� ���� ����� / ���� ��ȣ
		virtual void	receive_user_account_no(INT32 var) = 0;
		virtual PStr	receive_world_key() =0; //[?] ���� ���� ĳ���� ���� Ű
		virtual void	receive_world_key(PStr var) = 0;
		virtual INT64	receive_character_no() =0; //[8] ���� ���� ĳ���� ��ȣ
		virtual void	receive_character_no(INT64 var) = 0;
		virtual PStr	receive_character_id() =0; //[?] ���� ���� ĳ���� ���̵�
		virtual void	receive_character_id(PStr var) = 0;
		virtual PStr	send_message() =0; //[?] ���� �޽���
		virtual void	send_message(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopGift : public IResponseParent
	{
	public:
		IResponseWShopGift() {}
		virtual ~IResponseWShopGift() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual INT32	item_sale_no() =0; //[4] ������ �Ǹ� ��ȣ
		virtual void	item_sale_no(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT64	purchase_no() =0; //[8] ���� ��ȣ
		virtual void	purchase_no(INT64 var) = 0;
		virtual PStr	item_code() =0; //[?] ���ӿ��� ���� ������ ������ �ڵ� ��
		virtual void	item_code(PStr var) = 0;
		virtual INT32	item_minute() =0; //[4] ������ �Ⱓ(��)
		virtual void	item_minute(INT32 var) = 0;
		virtual SHORT	order_quantity() =0; //[2] �ֹ� ����
		virtual void	order_quantity(SHORT var) = 0;
		virtual PStr	attribute0() =0; //[?] �Ӽ� (Ŭ����� Property0) : optional
		virtual void	attribute0(PStr var) = 0;
		virtual PStr	attribute1() =0; //[?] �Ӽ� (Ŭ����� Property1) : optional
		virtual void	attribute1(PStr var) = 0;
		virtual PStr	attribute2() =0; //[?] �Ӽ� (Ŭ����� Property2) : optional
		virtual void	attribute2(PStr var) = 0;
		virtual PStr	attribute3() =0; //[?] �Ӽ� (Ŭ����� Property3) : optional
		virtual void	attribute3(PStr var) = 0;
		virtual PStr	attribute4() =0; //[?] �Ӽ� (Ŭ����� Property4) : optional
		virtual void	attribute4(PStr var) = 0;
	};
	// WShop Billing Step 7 : WShopCheckGift : ���� �� Ȯ��
	class IRequestWShopCheckGift : public IRequestParent
	{
	public:
		IRequestWShopCheckGift() {}
		virtual ~IRequestWShopCheckGift() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopCheckGift : public IResponseParent
	{
	public:
		IResponseWShopCheckGift() {}
		virtual ~IResponseWShopCheckGift() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] ���� �ֹ� ���� (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};
	// WShop Billing Step 8 : WShopCancelGift : ���� �� ���
	class IRequestWShopCancelGift : public IRequestParent
	{
	public:
		IRequestWShopCancelGift() {}
		virtual ~IRequestWShopCancelGift() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopCancelGift : public IResponseParent
	{
	public:
		IResponseWShopCancelGift() {}
		virtual ~IResponseWShopCancelGift() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// WShop Billing Step 9 : WShopConfirmGift : ��� ���� �� ����
	class IRequestWShopConfirmGift : public IRequestParent
	{
	public:
		IRequestWShopConfirmGift() {}
		virtual ~IRequestWShopConfirmGift() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopConfirmGift : public IResponseParent
	{
	public:
		IResponseWShopConfirmGift() {}
		virtual ~IResponseWShopConfirmGift() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// WShop Billing Step 10 : WShopGetVersion : �� ���� ���� ��ȸ
	class IRequestWShopGetVersion : public IRequestParent
	{
	public:
		IRequestWShopGetVersion() {}
		virtual ~IRequestWShopGetVersion() {}
	};
	class IResponseWShopGetVersion : public IResponseParent
	{
	public:
		IResponseWShopGetVersion() {}
		virtual ~IResponseWShopGetVersion() {}

		virtual INT64	shop_version() =0; //[8] ���� �� ����
		virtual void	shop_version(INT64 var) = 0;
	};

//## WShop Billing : END
//#################################################################################################
//##
//#################################################################################################
//## WShop Inventory : START
//##
	// WShop Inventory Step 1 : WShop Inquiry New Arrival : ���� �������� ���� ���� �κ��丮 ������ ��ȸ
	class IRequestWShopInquiryNewArrival : public IRequestParent
	{
	public:
		IRequestWShopInquiryNewArrival() {}
		virtual ~IRequestWShopInquiryNewArrival() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ�
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] ���ӿ��� �����ϴ� ���� Ű
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] ĳ���� ���̵�
		virtual void	character_id(PStr var) = 0;
		virtual INT64	standard_date_time() =0; //[8] ���� �ð�
		virtual void	standard_date_time(INT64 var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopInquiryNewArrival : public IResponseParent
	{
	public:
		IResponseWShopInquiryNewArrival() {}
		virtual ~IResponseWShopInquiryNewArrival() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual INT32	new_arrival_count() =0; //[4] ���� ���� ������ ��
		virtual void	new_arrival_count(INT32 var) = 0;
	};
	// WShop Inventory Step 2 : WShop Inquiry Inventory : �κ��丮 ��ȸ
	class IRequestWShopInquiryInventory : public IRequestParent
	{
	public:
		IRequestWShopInquiryInventory() {}
		virtual ~IRequestWShopInquiryInventory() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ�
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] ���ӿ��� �����ϴ� ���� Ű
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] ĳ���� ���̵�
		virtual void	character_id(PStr var) = 0;
		virtual BYTE	expand_flags() =0; //[1] Cash Inventory Item Expand Flags (Table 11 Inquiry Cash Inventory Expand Flags)
		virtual void	expand_flags(BYTE var) = 0;
		virtual INT32	page_index() =0; //[4] ������ ��ȣ
		virtual void	page_index(INT32 var) = 0;
		virtual INT32	row_per_page() =0; //[4] ������ �� ������ ������ ��
		virtual void	row_per_page(INT32 var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopInquiryInventory : public IResponseParent
	{
	public:
		IResponseWShopInquiryInventory() {}
		virtual ~IResponseWShopInquiryInventory() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual BYTE	expand_flags() =0; //[1] Cash Inventory Item Expand Flags (Table 11 Inquiry Cash Inventory Expand Flags)
		virtual void	expand_flags(BYTE var) = 0;
		virtual INT32	total_inventory_count() =0; //[4] �� �κ��丮 ��
		virtual void	total_inventory_count(INT32 var) = 0;
		virtual INT32	current_inventory_count() =0; //[4] ����� �κ��丮 ��
		virtual void	current_inventory_count(INT32 var) = 0;
		virtual IArrayPtr<IWShopInventoryItem*>* purchase_item_array() =0; //[?] ���� �κ��丮 ������ �迭
		virtual IArrayPtr<IWShopInventoryItem*>* package_item_array() =0; //[?] ���� �κ��丮 ������ �迭
		virtual IArrayPtr<IWShopInventoryItem*>* lottery_item_array() =0; //[?] ���� �κ��丮 ������ �迭
		virtual IArrayPtr<IWShopInventoryItem*>* bonus_item_array() =0; //[?] ���ʽ� �κ��丮 ������ �迭
	};
	// WShop Inventory Step 3 : WShop Pick Up : �κ��丮 ����
	class IRequestWShopPickUp : public IRequestParent
	{
	public:
		IRequestWShopPickUp() {}
		virtual ~IRequestWShopPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ�
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] ���ӿ��� �����ϴ� ���� Ű
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] ĳ���� ���̵�
		virtual void	character_id(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual INT64	purchase_no() =0; //[8] ������ ���� ��ȣ
		virtual void	purchase_no(INT64 var) = 0;
		virtual SHORT	order_quantity() =0; //[2] ���� ������ ��
		virtual void	order_quantity(SHORT var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ ������
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopPickUp : public IResponseParent
	{
	public:
		IResponseWShopPickUp() {}
		virtual ~IResponseWShopPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual IArrayPtr<IWShopPickUpItem*>* pick_up_item_array() =0; //[?] ���� ������ �迭
		virtual IArrayPtr<IJewelBalanceItem*>* jewel_balance_item_array() =0; //[?]2�� ȭ�� �ܾ� �迭 (��� ���� ���� ������ ���� �� ������Ʈ�� �ܾ��� ��ȯ�Ѵ�.)
	};
	// WShop Inventory Step 4 : WShop Check Pick Up : �κ��丮 ���� �� Ȯ��
	class IRequestWShopCheckPickUp : public IRequestParent
	{
	public:
		IRequestWShopCheckPickUp() {}
		virtual ~IRequestWShopCheckPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopCheckPickUp : public IResponseParent
	{
	public:
		IResponseWShopCheckPickUp() {}
		virtual ~IResponseWShopCheckPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] ���� �ֹ� ���� (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};
	// WShop Inventory Step 5 : WShop Cancel Pick Up : �κ��丮���ɰ����
	class IRequestWShopCancelPickUp : public IRequestParent
	{
	public:
		IRequestWShopCancelPickUp() {}
		virtual ~IRequestWShopCancelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�)(100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopCancelPickUp : public IResponseParent
	{
	public:
		IResponseWShopCancelPickUp() {}
		virtual ~IResponseWShopCancelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// WShop Inventory Step 6 : WShop Confirm Pick Up : �κ��丮���ɰǽ���
	class IRequestWShopConfirmPickUp : public IRequestParent
	{
	public:
		IRequestWShopConfirmPickUp() {}
		virtual ~IRequestWShopConfirmPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ�/���� �� ����ߴ� �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ����
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopConfirmPickUp : public IResponseParent
	{
	public:
		IResponseWShopConfirmPickUp() {}
		virtual ~IResponseWShopConfirmPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
	};

//## WShop Inventory : END
//#################################################################################################
//##
//#################################################################################################
//## Jewel Billing : START
//##
	// Jewel Step 1  : Charge Jewel : ���������û
	class IRequestChargeJewel : public IRequestParent
	{
	public:
		IRequestChargeJewel() {}
		virtual ~IRequestChargeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ�
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] ���ӿ��� �����ϴ� ���� Ű
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] ĳ���� ���̵�
		virtual void	character_id(PStr var) = 0;
		virtual INT32	game_level() =0; //[4] ���ӷ��� (������ ���  -1) : optional
		virtual void	game_level(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	payment_type() =0; //[?] ���� ���� (Table 19 Payment Type)
		virtual void	payment_type(PStr var) = 0;
		virtual INT32	cash_type() =0; //[?] ĳ�� Ÿ�� (Table 18 Cash Type)
		virtual void	cash_type(INT32 var) = 0;
		virtual PStr	item_code() = 0; //[?] ������ �ڵ�
		virtual void	item_code(PStr var) = 0;
		virtual PStr	payment_product_name() =0; //[?] ���� ��ǰ ��
		virtual void	payment_product_name(PStr var) = 0;
		virtual INT32	charge_amount() =0; //[4] ���� �ݾ�
		virtual void	charge_amount(INT32 var) = 0;
		virtual INT32	bonus_amount() =0; //[4] ���ʽ� ���� �ݾ�
		virtual void	bonus_amount(INT32 var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseChargeJewel : public IResponseParent
	{
	public:
		IResponseChargeJewel() {}
		virtual ~IResponseChargeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 2  : Check Jewel Charge : ���������Ȯ��
	class IRequestCheckJewelCharge : public IRequestParent
	{
	public:
		IRequestCheckJewelCharge() {}
		virtual ~IRequestCheckJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCheckJewelCharge : public IResponseParent
	{
	public:
		IResponseCheckJewelCharge() {}
		virtual ~IResponseCheckJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] ���� �ֹ� ���� (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};
	// Jewel Step 3  : Cancel Jewel Charge : ������������
	class IRequestCancelJewelCharge : public IRequestParent
	{
	public:
		IRequestCancelJewelCharge() {}
		virtual ~IRequestCancelJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�)(100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCancelJewelCharge : public IResponseParent
	{
	public:
		IResponseCancelJewelCharge() {}
		virtual ~IResponseCancelJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 4  : Confirm Jewel Charge : ��������ǽ���
	class IRequestConfirmJewelCharge : public IRequestParent
	{
	public:
		IRequestConfirmJewelCharge() {}
		virtual ~IRequestConfirmJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseConfirmJewelCharge : public IResponseParent
	{
	public:
		IResponseConfirmJewelCharge() {}
		virtual ~IResponseConfirmJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 5  : Purchase Jewel Item : ������
	class IRequestPurchaseJewelItem : public IRequestParent
	{
	public:
		IRequestPurchaseJewelItem() {}
		virtual ~IRequestPurchaseJewelItem() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ�
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] ���ӿ��� �����ϴ� ���� Ű
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] ĳ���� ���̵�
		virtual void	character_id(PStr var) = 0;
		virtual INT32	game_level() =0; //[4] ���ӷ��� (������ ���  -1) : optional
		virtual void	game_level(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	item_code() =0; //[?] ���ӿ��� �˰� �ִ� ������ �ĺ���
		virtual void	item_code(PStr var) = 0;
		virtual PStr	item_name() =0; //[?] ���ӿ��� �˰� �ִ� ������ ��
		virtual void	item_name(PStr var) = 0;
		virtual INT32	cash_type() =0; //[?] ���� ĳ�� ���� (Table 18 Cash Type)
		virtual void	cash_type(INT32 var) = 0;
		virtual INT32	purchase_cost() =0; //[4] ������ ����
		virtual void	purchase_cost(INT32 var) = 0;
		virtual INT32	purchase_quantity() =0; //[4] ������ ����
		virtual void	purchase_quantity(INT32 var) = 0;
		virtual INT32	purchase_amount() =0; //[4] �����Ϸ��� �������� �� �ݾ�
		virtual void	purchase_amount(INT32 var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponsePurchaseJewelItem : public IResponseParent
	{
	public:
		IResponsePurchaseJewelItem() {}
		virtual ~IResponsePurchaseJewelItem() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 6  : Check Purchase Jewel : ��������Ȯ��
	class IRequestCheckPurchaseJewel : public IRequestParent
	{
	public:
		IRequestCheckPurchaseJewel() {}
		virtual ~IRequestCheckPurchaseJewel() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCheckPurchaseJewel : public IResponseParent
	{
	public:
		IResponseCheckPurchaseJewel() {}
		virtual ~IResponseCheckPurchaseJewel() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 7  : Cancel Jewel Purchase : �����������
	class IRequestCancelJewelPurchase : public IRequestParent
	{
	public:
		IRequestCancelJewelPurchase() {}
		virtual ~IRequestCancelJewelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ�/���� �� ����ߴ� �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCancelJewelPurchase : public IResponseParent
	{
	public:
		IResponseCancelJewelPurchase() {}
		virtual ~IResponseCancelJewelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 8  : Confirm Jewel Purchase : �������ǽ���
	class IRequestConfirmJewelPurchase : public IRequestParent
	{
	public:
		IRequestConfirmJewelPurchase() {}
		virtual ~IRequestConfirmJewelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ�/���� �� ����ߴ� �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseConfirmJewelPurchase : public IResponseParent
	{
	public:
		IResponseConfirmJewelPurchase() {}
		virtual ~IResponseConfirmJewelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 9  : Trade Jewel : �������ŷ�
	class IRequestTradeJewel : public IRequestParent
	{
	public:
		IRequestTradeJewel() {}
		virtual ~IRequestTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] ���� ������ ���޵Ǵ� �Ӽ� : optional
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ�
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] ���ӿ��� �����ϴ� ���� Ű
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] ĳ���� ���̵�
		virtual void	character_id(PStr var) = 0;
		virtual INT32	game_level() =0; //[4] ���ӷ��� (������ ���  -1) : optional
		virtual void	game_level(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	item_code() =0; //[?] ���ӿ��� �˰� �ִ� ������ �ĺ���
		virtual void	item_code(PStr var) = 0;
		virtual PStr	item_name() =0; //[?] ���ӿ��� �˰� �ִ� ������ ��
		virtual void	item_name(PStr var) = 0;
		virtual INT32	purchase_cost() =0; //[4] ������ ����
		virtual void	purchase_cost(INT32 var) = 0;
		virtual INT32	purchase_quantity() =0; //[4] ���� ����
		virtual void	purchase_quantity(INT32 var) = 0;
		virtual INT32	purchase_amount() =0; //[4] �����Ϸ��� �������� �� �ݾ�
		virtual void	purchase_amount(INT32 var) = 0;
		virtual INT32	target_account_no() =0; //[4] �ŷ� ���(�������� �����) ����� ��ȣ     [����] ���� ��ȣ     [�۷ι�] ����� ��ȣ
		virtual void	target_account_no(INT32 var) = 0;
		virtual INT64	target_character_no() =0; //[8] �ŷ� ��� ĳ���� ��ȣ
		virtual void	target_character_no(INT64 var) = 0;
		virtual PStr	target_character_id() =0; //[?] �ŷ� ��� ĳ���� ���̵�
		virtual void	target_character_id(PStr var) = 0;
		virtual INT32	target_user_grade() =0; //[4] �ŷ� ���(����� ������ ��� ����)�� ����� ��� (Table 24 User Grade)
		virtual void	target_user_grade(INT32 var) = 0;
		virtual PStr	send_message() =0; //[?] �ŷ� �޽���
		virtual void	send_message(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseTradeJewel : public IResponseParent
	{
	public:
		IResponseTradeJewel() {}
		virtual ~IResponseTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 10 : Check Trade Jewel : �������ŷ���Ȯ�� 
	class IRequestCheckTradeJewel : public IRequestParent
	{
	public:
		IRequestCheckTradeJewel() {}
		virtual ~IRequestCheckTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCheckTradeJewel : public IResponseParent
	{
	public:
		IResponseCheckTradeJewel() {}
		virtual ~IResponseCheckTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] ���� �ֹ� ���� (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};
	// Jewel Step 11 : Cancel Jewel Trade : �������ŷ������
	class IRequestCancelJewelTrade : public IRequestParent
	{
	public:
		IRequestCancelJewelTrade() {}
		virtual ~IRequestCancelJewelTrade() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ�/���� �� ����ߴ� �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCancelJewelTrade : public IResponseParent
	{
	public:
		IResponseCancelJewelTrade() {}
		virtual ~IResponseCancelJewelTrade() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 12 : Confirm Jewel Trade : ��� ����� �ŷ��� ����
	class IRequestConfirmJewelTrade : public IRequestParent
	{
	public:
		IRequestConfirmJewelTrade() {}
		virtual ~IRequestConfirmJewelTrade() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] �ֹ�/���� �� ����ߴ� �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseConfirmJewelTrade : public IResponseParent
	{
	public:
		IResponseConfirmJewelTrade() {}
		virtual ~IResponseConfirmJewelTrade() {}

		virtual PStr	callback_attribute() =0; //[?] ���Ӽ����� ���޵Ǵ� �Ӽ� �� : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 13 : Pick Up Trade Jewel : ��� ����� �Ǹűݾ� ����(�Ǹ���)
	class IRequestPickUpTradeJewel : public IRequestParent
	{
	public:
		IRequestPickUpTradeJewel() {}
		virtual ~IRequestPickUpTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] ���� ������ ���޵Ǵ� �Ӽ� : optional
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	provider_code() =0; //[?] ���ι��̴� �ڵ� (Get User Info With Ext���� ���� ���� �״�� ����)
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] ����� ��ȣ
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] ����� ���̵�
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] ���� ��ȣ
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] ���� ���̵�
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] ���ӿ��� �����ϴ� ���� Ű
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] ĳ���� ��ȣ (�� �� ���ų� �Ǵ� ����� ��� 0���� ��)
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] ĳ���� ���̵� (�� �� ���� ��� �� ���ڿ�)
		virtual void	character_id(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	trade_order_id() =0; //[?] �� �������� �����ڰ� ����忡�� �������� �� �����ߴ� �ֹ���ȣ
		virtual void	trade_order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponsePickUpTradeJewel : public IResponseParent
	{
	public:
		IResponsePickUpTradeJewel() {}
		virtual ~IResponsePickUpTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] ���� ������ ���޵Ǵ� �Ӽ�
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT32	commission_amount() =0; //[4] �Ǹ� ������
		virtual void	commission_amount(INT32 var) = 0;
		virtual INT32	receive_amount() =0; //[4] (������ ���� ��) ���������� �Ǹ��ڰ� ���� ���� �ݾ�
		virtual void	receive_amount(INT32 var) = 0;
		virtual IArrayPtr<IJewelBalanceItem*>* jewel_balance_item_array() =0; //[?] 2�� ȭ�� �ܾ� �迭(�Ǹ� �ݾ� ���� ���� ������Ʈ�� �ܾ��� ��ȯ�Ѵ�.)
	};

	// Jewel Step 14 : Check Trade Jewel Pick Up : ����� �Ǹűݾ� ���ɰ� Ȯ��
	class IRequestCheckTradeJewelPickUp : public IRequestParent
	{
	public:
		IRequestCheckTradeJewelPickUp() {}
		virtual ~IRequestCheckTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���� ������ ���޵Ǵ� �Ӽ� : optional
		virtual void	callback_attribute(PStr var) = 0;
		virtual BYTE	return_structure_type() =0; //[1] ���� ����ü ���� (Table 5 Return Structure Types)
		virtual void	return_structure_type(BYTE var) = 0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ���ȣ (World�� ����ũ ���� �ʿ�) (100�ڱ��� ��밡��)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCheckTradeJewelPickUp : public IResponseParent
	{
	public:
		IResponseCheckTradeJewelPickUp() {}
		virtual ~IResponseCheckTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���� ������ ���޵Ǵ� �Ӽ�
		virtual void	callback_attribute(PStr var) = 0;
		virtual BYTE	return_structure_type() =0; //[1] ���� ����ü ���� (Table 5 Return Structure Types)
		virtual void	return_structure_type(BYTE var) = 0;
		virtual PStr	order_id() =0; //[?] �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] ���� �ֹ� ���� (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};
	// Jewel Step 15 : Cancel Trade Jewel Pick Up : ����� �Ǹűݾ� ���ɰ� ���
	class IRequestCancelTradeJewelPickUp : public IRequestParent
	{
	public:
		IRequestCancelTradeJewelPickUp() {}
		virtual ~IRequestCancelTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���� ������ ���޵Ǵ� �Ӽ� : optional
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] �ֹ�/���� �� ����ߴ� �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCancelTradeJewelPickUp : public IResponseParent
	{
	public:
		IResponseCancelTradeJewelPickUp() {}
		virtual ~IResponseCancelTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���� ������ ���޵Ǵ� �Ӽ�
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 16 : Confirm Trade Jewel Pick Up : ����� �Ǹűݾ� ���ɰ� ����
	class IRequestConfirmTradeJewelPickUp : public IRequestParent
	{
	public:
		IRequestConfirmTradeJewelPickUp() {}
		virtual ~IRequestConfirmTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���� ������ ���޵Ǵ� �Ӽ� : optional
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] �ֹ�/���� �� ����ߴ� �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] Ŭ���̾�Ʈ IP�ּ�
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseConfirmTradeJewelPickUp : public IResponseParent
	{
	public:
		IResponseConfirmTradeJewelPickUp() {}
		virtual ~IResponseConfirmTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] ���� ������ ���޵Ǵ� �Ӽ�
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
	};

//## Jewel Billing : END
//#################################################################################################
//##
//#################################################################################################
//## Advanced Biling - Cash Inventory : START
//##
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 1: Inquiry Cash Inventory - ĳ���κ��丮��ȸ
	class IRequestInquiryCashInventory : public IRequestParent
	{
	public:
		IRequestInquiryCashInventory()			{}
		virtual ~IRequestInquiryCashInventory()	{}

		//get,set
		virtual BYTE	item_expand_flag()				=0; //[1]Cash Inventory Item Expand Flags (fcs_constant.h�� "Table 11 Inquiry Cash Inventory Expand Flags" ����)
		virtual void	item_expand_flag(BYTE var)		=0;
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	page_index()					=0; //[4]��������ȣ
		virtual void	page_index(INT32 var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü������Ȯ��)
		virtual void	row_per_page(INT32 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseInquiryCashInventory : public IResponseParent
	{
	public:
		IResponseInquiryCashInventory()				{}
		virtual ~IResponseInquiryCashInventory()	{}

		//get,set
		virtual BYTE								item_expand_flag()			=0; //[1]Cash Inventory Item Expand Flags (Table 11 Inquiry Cash Inventory Expand Flags)
		virtual void								item_expand_flag(BYTE var)	=0;
		virtual	INT32								total_row_count()			=0; //[4]�κ��丮����
		virtual void								total_row_count(INT32 var)	=0;
		virtual IArrayPtr<ICashInventoryItems*>*	items()						=0; //[?]�����۱���ü�迭
		virtual IArrayPtr<IPackageItem*>*			package_items()				=0; //[?] ������ Ȥ�� item_expand_flag ���� ��� ����
		virtual IArrayPtr<ILotteryItem*>*			lottery_items()				=0; //[?] ������ Ȥ�� item_expand_flag ���� ��� ����
		virtual IArrayPtr<IBonusItem*>*				bonus_items()				=0; //[?] ������ Ȥ�� item_expand_flag ���� ��� ����
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 2: Inquiry Cash Inventory by Bind Attribute - ������ �ͼ� ���¿� ���� ĳ���κ��丮��ȸ
	class IRequestInquiryCashInventoryByBindAttribute : public IRequestParent
	{
	public:
		IRequestInquiryCashInventoryByBindAttribute()			{}
		virtual ~IRequestInquiryCashInventoryByBindAttribute()	{}

		//get,set
		virtual BYTE	item_expand_flag()				=0; //[1]Cash Inventory Item Expand Flags (fcs_constant.h�� "Table 11 Inquiry Cash Inventory Expand Flags" ����)
		virtual void	item_expand_flag(BYTE var)		=0;
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]���� ���̵�(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	page_index()					=0; //[4]��������ȣ
		virtual void	page_index(INT32 var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü������Ȯ��)
		virtual void	row_per_page(INT32 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseInquiryCashInventoryByBindAttribute : public IResponseParent
	{
	public:
		IResponseInquiryCashInventoryByBindAttribute()			{}
		virtual ~IResponseInquiryCashInventoryByBindAttribute()	{}

		//get,set
		virtual BYTE											item_expand_flag()			=0; //[1]Cash Inventory Item Expand Flags (Table 11 Inquiry Cash Inventory Expand Flags)
		virtual void											item_expand_flag(BYTE var)	=0;
		virtual	INT32											total_row_count()			=0; //[4]�κ��丮����
		virtual void											total_row_count(INT32 var)	=0;
		virtual IArrayPtr<ICashInventoryItemsByBindAttribute*>*	items()						=0; //[?]�����۱���ü�迭
		virtual IArrayPtr<IPackageItemByBindAttribute*>*		package_items()				=0; //[?] ������ Ȥ�� item_expand_flag ���� ��� ����
		virtual IArrayPtr<ILotteryItemByBindAttribute*>*		lottery_items()				=0; //[?] ������ Ȥ�� item_expand_flag ���� ��� ����
		virtual IArrayPtr<IBonusItemByBindAttribute*>*			bonus_items()				=0; //[?] ������ Ȥ�� item_expand_flag ���� ��� ����
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 3: Pickup Cash Inventory Item - ĳ���κ��丮����
	class IRequestPickupCashInventoryItem : public IRequestParent
	{
	public:
		IRequestPickupCashInventoryItem()			{}
		virtual ~IRequestPickupCashInventoryItem()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	optional_world_no()					=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۹�ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual bool	is_reserved_character()				=0; //[1]�������޵�ĳ�����������̿��ؼ������������ϰ���������(����ڰ��������α��Ÿ�����������������Ҽ��ִ�.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]�޴�Ÿ��. (fcs_constants.h - "ETC. Receive Type : �޴� Ÿ��" ����)
		virtual void	receive_type(BYTE var)				=0;
		virtual SHORT	pickup_quantity()					=0; //[2]���ɼ���
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]����
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponsePickupCashInventoryItem : public IResponseParent
	{
	public:
		IResponsePickupCashInventoryItem()			{}
		virtual ~IResponsePickupCashInventoryItem()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]��������
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 4: Pickup Cash Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ĳ���κ��丮����
	class IRequestPickupCashInventoryItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestPickupCashInventoryItemByBindAttribute()			{}
		virtual ~IRequestPickupCashInventoryItemByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]���� ID(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)				=0;
		virtual INT32	optional_world_no()					=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۹�ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual bool	is_reserved_character()				=0; //[1]�������޵�ĳ�����������̿��ؼ������������ϰ���������(����ڰ��������α��Ÿ�����������������Ҽ��ִ�.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]�޴�Ÿ��. (fcs_constants.h - "ETC. Receive Type : �޴� Ÿ��" ����)
		virtual void	receive_type(BYTE var)				=0;
		virtual SHORT	pickup_quantity()					=0; //[2]���ɼ���
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]����
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponsePickupCashInventoryItemByBindAttribute : public IResponseParent
	{
	public:
		IResponsePickupCashInventoryItemByBindAttribute()			{}
		virtual ~IResponsePickupCashInventoryItemByBindAttribute()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]��������
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 5: Cancel Pickup Cash Inventory Item - ĳ���κ��丮�������
	class IRequestCancelCashInventoryItem : public IRequestParent
	{
	public:
		IRequestCancelCashInventoryItem()			{}
		virtual ~IRequestCancelCashInventoryItem()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	optional_world_no()					=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۹�ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual bool	is_reserved_character()				=0; //[1]�������޵�ĳ�����������̿��ؼ������������ϰ���������(����ڰ��������α��Ÿ�����������������Ҽ��ִ�.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]�޴�Ÿ��. ��û����:0x01, �ڵ�����:0x02, ��������:0x03, ���ᰭ������:0x04, ����:0x05, �������:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual SHORT	pickup_quantity()					=0; //[2]���ɼ���
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]����
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponseCancelCashInventoryItem : public IResponseParent
	{
	public:
		IResponseCancelCashInventoryItem()			{}
		virtual ~IResponseCancelCashInventoryItem()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]��������
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 6: Cancel Pickup Cash Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ĳ���κ��丮�������
	class IRequestCancelCashInventoryItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestCancelCashInventoryItemByBindAttribute()			{}
		virtual ~IRequestCancelCashInventoryItemByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]���� ID(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)				=0;
		virtual INT32	optional_world_no()					=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۹�ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual bool	is_reserved_character()				=0; //[1]�������޵�ĳ�����������̿��ؼ������������ϰ���������(����ڰ��������α��Ÿ�����������������Ҽ��ִ�.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]�޴�Ÿ��. ��û����:0x01, �ڵ�����:0x02, ��������:0x03, ���ᰭ������:0x04, ����:0x05, �������:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual SHORT	pickup_quantity()					=0; //[2]���ɼ���
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]����
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponseCancelCashInventoryItemByBindAttribute : public IResponseParent
	{
	public:
		IResponseCancelCashInventoryItemByBindAttribute()			{}
		virtual ~IResponseCancelCashInventoryItemByBindAttribute()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]��������
		virtual void	remain_quantity(SHORT var)		=0;
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 7: Pickup Cash Sub Inventory Item - ����ĳ���κ��丮����
	class IRequestPickupCashSubInventoryItem : public IRequestParent
	{
	public:
		IRequestPickupCashSubInventoryItem()			{}
		virtual ~IRequestPickupCashSubInventoryItem()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	optional_world_no()					=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0;	//[4]�����۹�ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual INT64	inventory_no()						=0; //[8]�κ��丮��ȣ
		virtual void	inventory_no(INT64 var)				=0;
		virtual bool	is_reserved_character()				=0; //[1]�������޵�ĳ�����������̿��ؼ������������ϰ���������(����ڰ��������α��Ÿ�����������������Ҽ��ִ�.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]�޴�Ÿ��. ��û����:0x01, �ڵ�����:0x02, ��������:0x03, ���ᰭ������:0x04, ����:0x05, �������:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual BYTE	inventory_type()					=0; //[1]�κ��丮Ÿ��. Package Inventories:0x01, Lottery Inventories:0x02, Bonus Inventories:0x04
		virtual void	inventory_type(BYTE var)			=0;
		virtual SHORT	pickup_quantity()					=0; //[2]���ɼ���
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]����
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponsePickupCashSubInventoryItem : public IResponseParent
	{
	public:
		IResponsePickupCashSubInventoryItem()			{}
		virtual ~IResponsePickupCashSubInventoryItem()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]��������
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 8: Pickup Cash Sub Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ����ĳ���κ��丮����
	class IRequestPickupCashSubInventoryItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestPickupCashSubInventoryItemByBindAttribute()				{}
		virtual ~IRequestPickupCashSubInventoryItemByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]���� ID(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)				=0;
		virtual INT32	optional_world_no()					=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0;	//[4]�����۹�ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual INT64	inventory_no()						=0; //[8]�κ��丮��ȣ
		virtual void	inventory_no(INT64 var)				=0;
		virtual bool	is_reserved_character()				=0; //[1]�������޵�ĳ�����������̿��ؼ������������ϰ���������(����ڰ��������α��Ÿ�����������������Ҽ��ִ�.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]�޴�Ÿ��. ��û����:0x01, �ڵ�����:0x02, ��������:0x03, ���ᰭ������:0x04, ����:0x05, �������:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual BYTE	inventory_type()					=0; //[1]�κ��丮Ÿ��. Package Inventories:0x01, Lottery Inventories:0x02, Bonus Inventories:0x04
		virtual void	inventory_type(BYTE var)			=0;
		virtual SHORT	pickup_quantity()					=0; //[2]���ɼ���
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]����
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponsePickupCashSubInventoryItemByBindAttribute : public IResponseParent
	{
	public:
		IResponsePickupCashSubInventoryItemByBindAttribute()			{}
		virtual ~IResponsePickupCashSubInventoryItemByBindAttribute()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]��������
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 9: Cancel Cash Sub Inventory Item - ����ĳ���κ��丮���
	class IRequestCancelCashSubInventoryItem : public IRequestParent
	{
	public:
		IRequestCancelCashSubInventoryItem()			{}
		virtual ~IRequestCancelCashSubInventoryItem()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	optional_world_no()					=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۹�ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual INT64	inventory_no()						=0; //[8]�κ��丮��ȣ
		virtual void	inventory_no(INT64 var)				=0;
		virtual bool	is_reserved_character()				=0; //[1]�������޵�ĳ�����������̿��ؼ������������ϰ���������(����ڰ��������α��Ÿ�����������������Ҽ��ִ�.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]�޴�Ÿ��. ��û����:0x01, �ڵ�����:0x02, ��������:0x03, ���ᰭ������:0x04, ����:0x05, �������:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual BYTE	inventory_type()					=0; //[1]�κ��丮Ÿ��. Package Inventories:0x01, LotteryInventories:0x02, Bonus Inventories:0x04
		virtual void	inventory_type(BYTE var)			=0;
		virtual SHORT	pickup_quantity()					=0; //[2]���ɼ���
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]����
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponseCancelCashSubInventoryItem : public IResponseParent
	{
	public:
		IResponseCancelCashSubInventoryItem()			{}
		virtual ~IResponseCancelCashSubInventoryItem()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]��������
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 10: Cancel Cash Sub Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ����ĳ���κ��丮���
	class IRequestCancelCashSubInventoryItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestCancelCashSubInventoryItemByBindAttribute()				{}
		virtual ~IRequestCancelCashSubInventoryItemByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]���� ID(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)				=0;
		virtual INT32	optional_world_no()					=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۹�ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual INT64	inventory_no()						=0; //[8]�κ��丮��ȣ
		virtual void	inventory_no(INT64 var)				=0;
		virtual bool	is_reserved_character()				=0; //[1]�������޵�ĳ�����������̿��ؼ������������ϰ���������(����ڰ��������α��Ÿ�����������������Ҽ��ִ�.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]�޴�Ÿ��. ��û����:0x01, �ڵ�����:0x02, ��������:0x03, ���ᰭ������:0x04, ����:0x05, �������:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual BYTE	inventory_type()					=0; //[1]�κ��丮Ÿ��. Package Inventories:0x01, LotteryInventories:0x02, Bonus Inventories:0x04
		virtual void	inventory_type(BYTE var)			=0;
		virtual SHORT	pickup_quantity()					=0; //[2]���ɼ���
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]����
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponseCancelCashSubInventoryItemByBindAttribute : public IResponseParent
	{
	public:
		IResponseCancelCashSubInventoryItemByBindAttribute()			{}
		virtual ~IResponseCancelCashSubInventoryItemByBindAttribute()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]��������
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 11: Inquiry Pickup Standby Cash Purchase No - ���ӿ��� ���� ������ ������ ���Ź�ȣ ����Ʈ ��ȸ
	class IRequestInquiryPickupStandbyCashPurchaseNo : public IRequestParent
	{
	public:
		IRequestInquiryPickupStandbyCashPurchaseNo()			{}
		virtual ~IRequestInquiryPickupStandbyCashPurchaseNo()	{}

		//get,set
		virtual INT32	optional_world_no()				=0; //[4]Initialize ������ World No�� �ٸ� World No�� ��ȸ�� ��� ����Ѵ�. ����� ���� ��� -1 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]���� ID(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseInquiryPickupStandbyCashPurchaseNo : public IResponseParent
	{
	public:
		IResponseInquiryPickupStandbyCashPurchaseNo()			{}
		virtual ~IResponseInquiryPickupStandbyCashPurchaseNo()	{}

		//get,set
		virtual PStr						callback_attribute()		=0; //[?]��û�������ѼӼ���
		virtual void						callback_attribute(PStr var)=0;
		virtual INT32						total_row_count()			=0; //[4]��ü ������ ��
		virtual void						total_row_count(INT32 var)	=0;
		virtual IArrayPtr<IPurchaseNo*>*	purchase_nums()				=0; //[?]���Ź�ȣ ����ü �迭
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 12: Pickup Standby Cash Inventory - ���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �����·� ��ȯ
	class IRequestPickupStandbyCashInventory : public IRequestParent
	{
	public:
		IRequestPickupStandbyCashInventory()			{}
		virtual ~IRequestPickupStandbyCashInventory()	{}

		//get,set
		virtual BYTE	item_expand_flag()				=0; //[1]Cash Inventory Item Expand Flags (fcs_constant.h�� "Table 11 Inquiry Cash Inventory Expand Flags" ����)
		virtual void	item_expand_flag(BYTE var)		=0;
		virtual INT32	optional_world_no()				=0; //[4]Initialize ������ World No�� �ٸ� World No�� ��ȸ�� ��� ����Ѵ�. ����� ���� ��� -1 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]���� ID(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT64	purchase_no()					=0; //[8]���� ��ȣ
		virtual void	purchase_no(INT64 var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponsePickupStandbyCashInventory : public IResponseParent		// ����ȭ ��û�� ���� �������̽� ���� ����
	{
	public:
		IResponsePickupStandbyCashInventory()			{}
		virtual ~IResponsePickupStandbyCashInventory()	{}

		//get,set
		virtual PStr											callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void											callback_attribute(PStr var)	=0;
		virtual	INT32											total_row_count()				=0; //[4]��ü ������ ��
		virtual void											total_row_count(INT32 var)		=0;
		virtual INT64											purchase_no()					=0;	//[8]���� ��ȣ
		virtual void											purchase_no(INT64 var)			=0;
		virtual INT32											user_no()						=0;	//[4]����� ��ȣ
		virtual void											user_no(INT32 var)				=0;
		virtual INT32											account_no()					=0;	//[4]���� ��ȣ
		virtual void											account_no(INT32 var)			=0;
		virtual INT32											character_no()					=0; //[4]ĳ���͹�ȣ
		virtual void											character_no(INT32 var)			=0;
		virtual INT32											world_no()						=0; //[4]���� ��ȣ
		virtual void											world_no(INT32 var)				=0;
		virtual IArrayPtr<IPickupStandbyCashInventoryItem*>*	items()							=0; //[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 13: Complete Pickup Standby Cash Inventory - ���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �Ϸ���·� ��ȯ
	class IRequestCompletePickupStandbyCashInventory : public IRequestParent
	{
	public:
		IRequestCompletePickupStandbyCashInventory()			{}
		virtual ~IRequestCompletePickupStandbyCashInventory()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual INT32	account_no()					=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]Initialize ������ World No�� �ٸ� World No�� ��ȸ�� ��� ����Ѵ�. ����� ���� ��� -1 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual INT32	character_no()					=0;	//[4]ĳ���� ��ȣ (�����ͼ��� ��� -1)
		virtual void	character_no(INT32 var)			=0;
		virtual INT64	purchase_no()					=0; //[8]�ֹ� ��ȣ
		virtual void	purchase_no(INT64 var)			=0;
		virtual INT32	item_no()						=0;	//[4]������ ��ȣ(��Ű�� ���� ������ ��ȣ)
		virtual void	item_no(INT32 var)				=0;
		virtual SHORT	pickup_quantity()				=0;	//[2]���� ����
		virtual void	pickup_quantity(SHORT var)		=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		
	};
	class IResponseCompletePickupStandbyCashInventory : public IResponseParent
	{
	public:
		IResponseCompletePickupStandbyCashInventory()			{}
		virtual ~IResponseCompletePickupStandbyCashInventory()	{}

		//get,set
		virtual INT64	purchase_no()					=0; //[8]�ֹ� ��ȣ
		virtual void	purchase_no(INT64 var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 14: Cancel Pickup Standby Cash Inventory - ���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �����¿��� ���
	class IRequestCancelPickupStandbyCashInventory : public IRequestParent
	{
	public:
		IRequestCancelPickupStandbyCashInventory()			{}
		virtual ~IRequestCancelPickupStandbyCashInventory()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual INT32	account_no()					=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]Initialize ������ World No�� �ٸ� World No�� ��ȸ�� ��� ����Ѵ�. ����� ���� ��� -1 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual INT32	character_no()					=0;	//[4]ĳ���� ��ȣ (�����ͼ��� ��� -1)
		virtual void	character_no(INT32 var)			=0;
		virtual INT64	purchase_no()					=0; //[8]�ֹ� ��ȣ
		virtual void	purchase_no(INT64 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		
	};
	class IResponseCancelPickupStandbyCashInventory : public IResponseParent
	{
	public:
		IResponseCancelPickupStandbyCashInventory()				{}
		virtual ~IResponseCancelPickupStandbyCashInventory()	{}

		//get,set
		virtual INT64	purchase_no()					=0; //[8]�ֹ� ��ȣ
		virtual void	purchase_no(INT64 var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]��û�������ѼӼ���
		virtual void	callback_attribute(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 15: Use Storage - IBS ������ ��ǰ ���
	class IRequestUseStorage : public IRequestParent
	{
	public:
		IRequestUseStorage()			{}
		virtual ~IRequestUseStorage()	{}
		
		//get,set
		virtual INT32	account_no()				=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)		=0;
		virtual INT32	game_code()					=0; //[4]���� �ڵ�
		virtual void	game_code(INT32 var)		=0;
		virtual INT32	server_seq()				=0; //[4]���� ���� ����(������ ������ ��ǰ ��� ��, �� �� -1)
		virtual void	server_seq(INT32 var)		=0;
		virtual PStr	client_ip()					=0; //[?]����� IP �ּ�
		virtual void	client_ip(PStr var)			=0;
		virtual INT32	storage_seq()				=0; //[4]������ ����
		virtual void	storage_seq(INT32 var)		=0;
		virtual INT32	storage_item_seq()			=0; //[4]������ ��ǰ ����
		virtual void	storage_item_seq(INT32 var)	=0;
		virtual INT32	char_class()				=0; //[4]ĳ���� Ŭ����(������ 0)
		virtual void	char_class(INT32 var)		=0;
		virtual INT32	char_level()				=0; //[4]ĳ���� ����(������ 0)
		virtual void	char_level(INT32 var)		=0;
		virtual PStr	char_name()					=0; //[?]ĳ���� ��
		virtual void	char_name(PStr var)			=0;
		virtual PStr	char_rank()					=0; //[?]ĳ���� ��ũ
		virtual void	char_rank(PStr var)			=0;
		virtual INT32	server_index()				=0; //[4]���� ��ȣ
		virtual void	server_index(INT32 var)		=0;
	};
	class IResponseUseStorage : public IResponseParent
	{
	public:
		IResponseUseStorage()			{}
		virtual ~IResponseUseStorage()	{}
		
		//get,set
		virtual INT32	account_no()							=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)					=0;
		virtual INT32	ibs_result()							=0;	//[4]IBS ó�� �����
		virtual void	ibs_result(INT32 var)					=0;
		virtual INT32	server_seq()							=0; //[4]���� ���� ���� ��
		virtual void	server_seq(INT32 var)					=0;
		virtual PStr	in_game_product_id()					=0; //[?]���ӿ��� ����ϴ� ������ �ڵ�
		virtual void	in_game_product_id(PStr var)			=0;
		virtual INT32	product_seq()							=0; //[4]��ǰ ��ȣ
		virtual void	product_seq(INT32 var)					=0;
		virtual INT32	storage_seq()							=0; //[4]������ ��ȣ
		virtual void	storage_seq(INT32 var)					=0;
		virtual INT32	storage_item_seq()						=0; //[4]������ ĳ�� or ��ǰ ��ȣ
		virtual void	storage_item_seq(INT32 var)				=0;
		virtual INT32	property_count()						=0; //[4]�Ӽ� ����
		virtual void	property_count(INT32 var)				=0;
		virtual IArrayPtr<ISTItemProperty*>*	property_list()	=0; //[?]STItemProperty Structure �迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 16: Rollback Use Storage - IBS ������ ��� �ѹ�
	class IRequestRollbackUseStorage : public IRequestParent
	{
	public:
		IRequestRollbackUseStorage()			{}
		virtual ~IRequestRollbackUseStorage()	{}
		
		//get,set
		virtual INT32	account_no()				=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)		=0;
		virtual INT32	game_code()					=0; //[4]���� �ڵ�
		virtual void	game_code(INT32 var)		=0;
		virtual INT32	storage_seq()				=0; //[4]������ ����
		virtual void	storage_seq(INT32 var)		=0;
		virtual INT32	storage_item_seq()			=0; //[4]������ ��ǰ ����
		virtual void	storage_item_seq(INT32 var)	=0;
	};
	class IResponseRollbackUseStorage : public IResponseParent
	{
	public:
		IResponseRollbackUseStorage()			{}
		virtual ~IResponseRollbackUseStorage()	{}
		
		//get,set
		virtual INT32	account_no()				=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)		=0;
		virtual INT32	ibs_result()				=0; //[4]IBS ó�� �����
		virtual void	ibs_result(INT32 var)		=0;
	};


//## Advanced Biling - Cash Inventory : END
//#################################################################################################
//##
//#################################################################################################
//## Advanced Biling - Inquiry OData : START
//##
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Inquiry OData Step 1: Inquiry Service Metadata : OData�� ���� Metadata ��ȸ
	class IRequestInquiryServiceMetadata : public IRequestParent
	{
	public:
		IRequestInquiryServiceMetadata()			{}
		virtual ~IRequestInquiryServiceMetadata()	{}

		//get,set
		virtual PStr	client_ip()				=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)		=0;
	};
	class IResponseInquiryServiceMetadata : public IResponseParent
	{
	public:
		IResponseInquiryServiceMetadata()			{}
		virtual ~IResponseInquiryServiceMetadata()	{}

		//get,set
		virtual PStr	json()			=0;	//[?]�����ϰ� �ִ� Metadata JSON ����
		virtual void	json(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Inquiry OData Step 2: Inquiry OData Service: OData ��ȸ (��ǰ ����)
	class IRequestInquiryODataService : public IRequestParent
	{
	public:
		IRequestInquiryODataService()			{}
		virtual ~IRequestInquiryODataService()	{}

		//get,set
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual BYTE	execute_method_type()			=0; //[1]��ȸ�Ҹ޼ҵ�Ÿ��(fcs_Constant.h - Table 16 Execute Method Type)
		virtual void	execute_method_type(BYTE var)	=0;
		virtual PStr	expand()						=0; //[?]Entity Ȯ��(OData URL Conventions����)(�˼����������ڿ�) - http://www.odata.org/media/30002/OData%20URL%20Conventions.html
		virtual void	expand(PStr var)				=0;
		virtual PStr	filter()						=0; //[?]�˻�����(OData URL Conventions����)(�˼����������ڿ�) - http://www.odata.org/media/30002/OData%20URL%20Conventions.html
		virtual void	filter(PStr var)				=0;
		virtual PStr	select()						=0; //[?]�÷�(OData URL Conventions����)(�˼����������ڿ�) - http://www.odata.org/media/30002/OData%20URL%20Conventions.html
		virtual void	select(PStr var)				=0;
		virtual PStr	order_by()						=0; //[?]��������(OData URL Conventions����)(�˼����������ڿ�) - http://www.odata.org/media/30002/OData%20URL%20Conventions.html
		virtual void	order_by(PStr var)				=0;
		virtual INT32	page_index()					=0; //[4]��������ȣ
		virtual void	page_index(INT32 var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü�����͸�Ȯ���Ҽ��ִ�.)
		virtual void	row_per_page(INT32 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseInquiryODataService : public IResponseParent
	{
	public:
		IResponseInquiryODataService()			{}
		virtual ~IResponseInquiryODataService()	{}

		//get,set
		virtual INT64	item_version()				=0; //[8]�� ������ ����
		virtual void	item_version(INT64 var)		=0;
		virtual INT32	total_count()				=0; //[4]��ü ī��Ʈ
		virtual void	total_count(INT32 var)		=0;
		virtual PStr	json()						=0;	//[?]JSON ����
		virtual void	json(PStr var)				=0;
	};

//## Advanced Biling - Inquiry OData : END
//#################################################################################################
//##
//#################################################################################################
//## Advanced Biling - Cart & Wish Items : START
//##
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 1: Inquiry Cart Items : ����īƮ��ȸ
	class IRequestInquiryCartItems : public IRequestParent
	{
	public:
		IRequestInquiryCartItems()			{}
		virtual ~IRequestInquiryCartItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	page_index()					=0; //[4]��������ȣ
		virtual void	page_index(INT32 var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü������Ȯ��)
		virtual void	row_per_page(INT32 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseInquiryCartItems : public IResponseParent
	{
	public:
		IResponseInquiryCartItems()			{}
		virtual ~IResponseInquiryCartItems()	{}

		//get,set
		virtual INT32	total_items_count()				=0; //[4]����īƮ����
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<ICartItemInfo*>*	items()		=0;	//[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 2: Register Cart Items : ����īƮ��ǰ���
	class IRequestRegisterCartItems : public IRequestParent
	{
	public:
		IRequestRegisterCartItems()				{}
		virtual ~IRequestRegisterCartItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü������Ȯ��)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRegisterItem*>*	items()		=0; //[?]����īƮ������Ҿ����۱���ü�迭
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseRegisterCartItems : public IResponseParent
	{
	public:
		IResponseRegisterCartItems()			{}
		virtual ~IResponseRegisterCartItems()	{}

		//get,set
		virtual INT32	total_items_count()				=0; //[4]����īƮ����
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<ICartItemInfo*>*	items()		=0; //[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 3: Modify Cart Items Quantity : ����īƮ�����ۺ���
	class IRequestModifyCartItemsQuantity : public IRequestParent
	{
	public:
		IRequestModifyCartItemsQuantity()			{}
		virtual ~IRequestModifyCartItemsQuantity()	{}

		//get,set
		virtual INT64	cart_no()						=0; //[8]īƮ��ȣ
		virtual void	cart_no(INT64 var)				=0;
		virtual SHORT	purchase_quantity()				=0; //[2]�ֹ�����
		virtual void	purchase_quantity(SHORT var)	=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseModifyCartItemsQuantity : public IResponseParent
	{
	public:
		IResponseModifyCartItemsQuantity()			{}
		virtual ~IResponseModifyCartItemsQuantity()	{}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 4: Modify Cart Items Attribute : ����īƮ�����ۺ���
	class IRequestModifyCartItemsAttribute : public IRequestParent
	{
	public:
		IRequestModifyCartItemsAttribute()			{}
		virtual ~IRequestModifyCartItemsAttribute()	{}

		//get,set
		virtual INT64	cart_no()						=0; //[8]īƮ��ȣ
		virtual void	cart_no(INT64 var)				=0;
		virtual PStr	attribute0()					=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)			=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;

	};
	class IResponseModifyCartItemsAttribute : public IResponseParent
	{
	public:
		IResponseModifyCartItemsAttribute()			{}
		virtual ~IResponseModifyCartItemsAttribute()	{}
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 5: Remove Cart Items : ����īƮ�����ۻ���
	class IRequestRemoveCartItems : public IRequestParent
	{
	public:
		IRequestRemoveCartItems()			{}
		virtual ~IRequestRemoveCartItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü������Ȯ��)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRequestNo*>*	items()			=0; //[?]����īƮ����������īƮ����ü�迭
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseRemoveCartItems : public IResponseParent
	{
	public:
		IResponseRemoveCartItems()			{}
		virtual ~IResponseRemoveCartItems()	{}

		//get,set
		virtual	INT32	total_items_count()				=0; //[4]����īƮ����
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<ICartItemInfo*>*	items()		=0; //[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 6: Remove Cart : ����īƮ�ʱ�ȭ
	class IRequestRemoveCart : public IRequestParent
	{
	public:
		IRequestRemoveCart()			{}
		virtual ~IRequestRemoveCart()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseRemoveCart : public IResponseParent
	{
	public:
		IResponseRemoveCart()			{}
		virtual ~IResponseRemoveCart()	{}
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 7: Cart Items Transfer Wish Items : ���þ��������� ����īƮ ������ �̵�
	class IRequestCartItemsTransferWishItems : public IRequestParent
	{
	public:
		IRequestCartItemsTransferWishItems()			{}
		virtual ~IRequestCartItemsTransferWishItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü������Ȯ��)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRequestNo*>*	items()			=0; //[?]����īƮ���� �̵��� īƮ ����ü �迭
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseCartItemsTransferWishItems : public IResponseParent
	{
	public:
		IResponseCartItemsTransferWishItems()			{}
		virtual ~IResponseCartItemsTransferWishItems()	{}

		//get,set
		virtual	INT32	total_items_count()				=0; //[4]��������īƮ����
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<ICartItemInfo*>*	items()		=0; //[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 8: Inquiry Wish Items : ���þ�������ȸ
	class IRequestInquiryWishItems : public IRequestParent
	{
	public:
		IRequestInquiryWishItems()			{}
		virtual ~IRequestInquiryWishItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	page_index()					=0; //[4]��������ȣ
		virtual void	page_index(INT32 var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü������Ȯ��)
		virtual void	row_per_page(INT32 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseInquiryWishItems : public IResponseParent
	{
	public:
		IResponseInquiryWishItems()				{}
		virtual ~IResponseInquiryWishItems()	{}

		//get,set
		virtual	INT32	expand_item_flags()				=0; //[4]Expand Item Flags (fcs_constant.h - Table 15 Inquiry Cart & Wish Expand Flags)
		virtual void	expand_item_flags(INT32 var)	=0;
		virtual	INT32	total_items_count()				=0; //[4]���þ������Ѽ���
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IWishItemInfo*>*	items()		=0; //[?]�����۱���ü�迭
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 9: Register Wish Items : Wish ����Ʈ��ǰ���
	class IRequestRegisterWishItems : public IRequestParent
	{
	public:
		IRequestRegisterWishItems()				{}
		virtual ~IRequestRegisterWishItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü������Ȯ��)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRegisterItem*>* items()		=0; //[?]���ø���Ʈ������Ҿ����۱���ü�迭
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseRegisterWishItems : public IResponseParent
	{
	public:
		IResponseRegisterWishItems()			{}
		virtual ~IResponseRegisterWishItems()	{}

		//get,set
		virtual	INT32	expand_item_flags()				=0; //[4]Expand Item Flags (Table 15 Inquiry Cart & Wish Expand Flags)
		virtual void	expand_item_flags(INT32 var)	=0;
		virtual	INT32	total_items_count()				=0; //[4]���þ������Ѽ���
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IWishItemInfo*>*	items()		=0; //[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 10: Remove Wish Items : ���� ������ ����
	class IRequestRemoveWishItems : public IRequestParent
	{
	public:
		IRequestRemoveWishItems()			{}
		virtual ~IRequestRemoveWishItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü������Ȯ��)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRequestNo*>*	items()			=0; //[?]���ø���Ʈ����������īƮ����ü�迭
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseRemoveWishItems : public IResponseParent
	{
	public:
		IResponseRemoveWishItems()			{}
		virtual ~IResponseRemoveWishItems()	{}

		//get,set
		virtual	INT32	expand_item_flags()				=0; //[4]Expand Item Flags (Table 15 Inquiry Cart & Wish Expand Flags)
		virtual void	expand_item_flags(INT32 var)	=0;
		virtual	INT32	total_items_count()				=0; //[4]���þ�������ü����
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IWishItemInfo*>*	items()		=0; //[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 11: Remove Wish : ���� ������ �ʱ�ȭ
	class IRequestRemoveWish : public IRequestParent
	{
	public:
		IRequestRemoveWish()			{}
		virtual ~IRequestRemoveWish()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseRemoveWish : public IResponseParent
	{
	public:
		IResponseRemoveWish()			{}
		virtual ~IResponseRemoveWish()	{}
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 12: Wish Items Transfer Cart Items : ����īƮ�� ���� ������ �̵�
	class IRequestWishItemsTransferCartItems : public IRequestParent
	{
	public:
		IRequestWishItemsTransferCartItems()			{}
		virtual ~IRequestWishItemsTransferCartItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]�������絥���Ͱ���(0���϶Ǵ� 0x7FFFFFFF�̸���ü������Ȯ��)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRequestNo*>*	items()			=0; //[?]���ø���Ʈ���� �̵��� ����ü �迭
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseWishItemsTransferCartItems : public IResponseParent
	{
	public:
		IResponseWishItemsTransferCartItems()			{}
		virtual ~IResponseWishItemsTransferCartItems()	{}

		//get,set
		virtual	INT32	total_items_count()				=0; //[4]��������īƮ����
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IWishItemInfo*>*	items()		=0; //[?]�����۱���ü�迭
	};

//## Advanced Biling - Cart & Wish Items : END
//#################################################################################################
//##
//#################################################################################################
//## Advanced Biling - Order : START
//##	GP2.0 �����ۼ��ý��ۿ����µ�ϵȾ����ۼӼ������󼭻���ڶǴ�ĳ���ʹ����� Cash Inventory�������Ҽ��ִ�.
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 1: Shop Direct Purchase Item : �ٷα���
	class IRequestShopDirectPurchaseItem : public IRequestParent
	{
	public:
		IRequestShopDirectPurchaseItem()			{}
		virtual ~IRequestShopDirectPurchaseItem()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]�����Ǵ���������(�����Ұ��99)
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]���ӷ���
		virtual void	game_level(INT32 var)			=0;
		virtual PStr	order_id()						=0; //[?]���ӿ�������������ũ���ֹ���ȣ(World������ũ�����ʿ�)
		virtual void	order_id(PStr var)				=0;
		virtual INT32	category_no()					=0; //[4]ī�װ���ȣ
		virtual void	category_no(INT32 var)			=0;
		virtual INT32	item_no()						=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)				=0;
		virtual PStr	item_type()						=0; //[?]������Ÿ��
		virtual void	item_type(PStr var)				=0;
		virtual PStr	sale_type()						=0; //[?]�Ǹ�Ÿ��
		virtual void	sale_type(PStr var)				=0;
		virtual SHORT	order_quantity()				=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)		=0;		
		virtual INT32	purchase_price()				=0;	//[4]���� �ݾ� (���η� �ִ°��� ���� ����� �ݾ�)
		virtual void	purchase_price(INT32 var)		=0;
		virtual PStr	item_sale_type()				=0; //[?]�������Ǹ�����
		virtual void	item_sale_type(PStr var)		=0;
		virtual PStr	purchase_type()					=0; //[?]����Ÿ��
		virtual void	purchase_type(PStr var)			=0;
		virtual BYTE	inventory_status()				=0; //[1]�κ��丮����(��ü���:kISImmediately(0x1F), �Ⱦ������Ѽ���:kISPickup(0x05))
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	attribute0()					=0; //[?]�Ӽ�(Ŭ����� Property0)
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]�Ӽ�(Ŭ����� Property1)
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]�Ӽ�(Ŭ����� Property2)
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]�Ӽ�(Ŭ����� Property3)
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]�Ӽ�(Ŭ����� Property4)
		virtual void	attribute4(PStr var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]����
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]Ŭ���̾�ƮIP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopDirectPurchaseItem : public IResponseParent
	{
	public:
		IResponseShopDirectPurchaseItem()			{}
		virtual ~IResponseShopDirectPurchaseItem()	{}

		//get,set
		virtual	INT32	total_items_count()				=0; //[4]���ֹ�����
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IApprovalItem*>*	items()		=0; //[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 2: Shop Direct Purchase Item by Bind Attribute : ������ �ͼ� ���¿� ���� �ٷα���
	class IRequestShopDirectPurchaseItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestShopDirectPurchaseItemByBindAttribute()				{}
		virtual ~IRequestShopDirectPurchaseItemByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]���� ID(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]�����Ǵ���������(�����Ұ��99)
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]���ӷ���
		virtual void	game_level(INT32 var)			=0;
		virtual PStr	order_id()						=0; //[?]���ӿ�������������ũ���ֹ���ȣ(World������ũ�����ʿ�)
		virtual void	order_id(PStr var)				=0;
		virtual INT32	category_no()					=0; //[4]ī�װ���ȣ
		virtual void	category_no(INT32 var)			=0;
		virtual INT32	item_no()						=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)				=0;
		virtual PStr	item_type()						=0; //[?]������Ÿ��
		virtual void	item_type(PStr var)				=0;
		virtual PStr	sale_type()						=0; //[?]�Ǹ�Ÿ��
		virtual void	sale_type(PStr var)				=0;
		virtual SHORT	order_quantity()				=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)		=0;		
		virtual INT32	purchase_price()				=0;	//[4]���� �ݾ� (���η� �ִ°��� ���� ����� �ݾ�)
		virtual void	purchase_price(INT32 var)		=0;
		virtual PStr	item_sale_type()				=0; //[?]�������Ǹ�����
		virtual void	item_sale_type(PStr var)		=0;
		virtual PStr	purchase_type()					=0; //[?]����Ÿ��
		virtual void	purchase_type(PStr var)			=0;
		virtual BYTE	inventory_status()				=0; //[1]�κ��丮����(��ü���:kISImmediately(0x1F), �Ⱦ������Ѽ���:kISPickup(0x05))
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	attribute0()					=0; //[?]�Ӽ�(Ŭ����� Property0)
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]�Ӽ�(Ŭ����� Property1)
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]�Ӽ�(Ŭ����� Property2)
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]�Ӽ�(Ŭ����� Property3)
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]�Ӽ�(Ŭ����� Property4)
		virtual void	attribute4(PStr var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]����
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]Ŭ���̾�ƮIP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopDirectPurchaseItemByBindAttribute : public IResponseParent
	{
	public:
		IResponseShopDirectPurchaseItemByBindAttribute()			{}
		virtual ~IResponseShopDirectPurchaseItemByBindAttribute()	{}

		//get,set
		virtual	INT32	total_items_count()				=0; //[4]���ֹ�����
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IApprovalItem*>*	items()		=0; //[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 3: Shop Purchase Cart Items : ����īƮ����
	class IRequestShopPurchaseCartItems : public IRequestParent
	{
	public:
		IRequestShopPurchaseCartItems()				{}
		virtual ~IRequestShopPurchaseCartItems()	{}
		
		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]�����Ǵ���������
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]���ӷ���
		virtual void	game_level(INT32 var)			=0;
		virtual PStr	order_id()						=0; //[?]���ӿ�������������ũ���ֹ���ȣ(World������ũ�����ʿ�)
		virtual void	order_id(PStr var)				=0;
		virtual IArrayPtr<ICartItem*>* items()			=0; //[?]����īƮ�����ֹ��ұ���ü�迭
		virtual BYTE	inventory_status()				=0; //[1]�κ��丮����(��ü���:0x1E, �Ⱦ������Ѽ���:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]����
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]Ŭ���̾�ƮIP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopPurchaseCartItems : public IResponseParent
	{
	public:
		IResponseShopPurchaseCartItems()			{}
		virtual ~IResponseShopPurchaseCartItems()	{}
		
		//get,set
		virtual INT32	total_items_count()					=0; //[4]���ֹ�����
		virtual void	total_items_count(INT32 var)		=0;
		virtual	IArrayPtr<IApprovalItem*>* items()			=0; //[?]�����۱���ü�迭
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 4: Shop Direct Gift Item : �ٷμ���
	class IRequestShopDirectGiftItem : public IRequestParent
	{
	public:
		IRequestShopDirectGiftItem()			{}
		virtual ~IRequestShopDirectGiftItem()	{}
		
		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]�����Ǵ���������
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]���ӷ���
		virtual void	game_level(INT32 var)			=0;
		virtual INT32	receive_user_no()				=0; //[4]������������ڹ�ȣ(�˼�������� -1)
		virtual void	receive_user_no(INT32 var)		=0;
		virtual PStr	receive_user_id()				=0; //[?]������������ھ��̵�(�˼����������ڿ�)
		virtual void	receive_user_id(PStr var)		=0;
		virtual INT32	receive_word_no()				=0; //[4]�������������ȣ(�˼�������� -1)
		virtual void	receive_word_no(INT32 var)		=0;
		virtual PStr	receive_word_key()				=0; //[?]������������Ű(�˼����������ڿ�)
		virtual void	receive_word_key(PStr var)		=0;
		virtual INT32	receive_character_no()			=0; //[4]��������ĳ���͹�ȣ(�˼�������� -1)
		virtual void	receive_character_no(INT32 var)	=0;
		virtual PStr	receive_character_id()			=0; //[?]��������ĳ���;��̵�(�˼����������ڿ�)
		virtual void	receive_character_id(PStr var)	=0;
		virtual PStr	send_message()					=0; //[?]�����޽���
		virtual void	send_message(PStr var)			=0;
		virtual PStr	order_id()						=0; //[?]���ӿ�������������ũ���ֹ���ȣ(World������ũ�����ʿ�)
		virtual void	order_id(PStr var)				=0;
		virtual INT32	category_no()					=0; //[4]ī�װ���ȣ
		virtual void	category_no(INT32 var)			=0;
		virtual INT32	item_no()						=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)				=0;
		virtual PStr	item_type()						=0; //[?]������Ÿ��
		virtual void	item_type(PStr var)				=0;
		virtual PStr	sale_type()						=0; //[?]�Ǹ�Ÿ��
		virtual void	sale_type(PStr var)				=0;
		virtual SHORT	order_quantity()				=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)		=0;
		virtual INT32	purchase_price()				=0;	//[4]���� �ݾ� (���η� �ִ°��� ���� ����� �ݾ�)
		virtual void	purchase_price(INT32 var)		=0;
		virtual PStr	item_sale_type()				=0; //[?]�������Ǹ�����
		virtual void	item_sale_type(PStr var)		=0;
		virtual PStr	purchase_type()					=0; //[?]����Ÿ��
		virtual void	purchase_type(PStr var)			=0;
		virtual BYTE	inventory_status()				=0; //[1]�κ��丮����(��ü���:0x1E, �Ⱦ������Ѽ���:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	attribute0()					=0; //[?]�Ӽ�
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]�Ӽ�
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]�Ӽ�
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]�Ӽ�
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]�Ӽ�
		virtual void	attribute4(PStr var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]����
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]Ŭ���̾�ƮIP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopDirectGiftItem : public IResponseParent
	{
	public:
		IResponseShopDirectGiftItem()			{}
		virtual ~IResponseShopDirectGiftItem()	{}
		
		//get,set
		virtual INT32	total_items_count()				=0; //[4]���ֹ�����
		virtual void	total_items_count(INT32 var)	=0;
		virtual	IArrayPtr<IApprovalItem*>* items()		=0; //[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 5: Shop Direct Gift Item by Bind Attribute : ������ �ͼ� ���¿� ���� �ٷμ���
	class IRequestShopDirectGiftItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestShopDirectGiftItemByBindAttribute()				{}
		virtual ~IRequestShopDirectGiftItemByBindAttribute()	{}
		
		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]���� ID(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]�����Ǵ���������
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]���ӷ���
		virtual void	game_level(INT32 var)			=0;
		virtual INT32	receive_user_no()				=0; //[4]���� ���� ����� ��ȣ(�˼�������� -1)
		virtual void	receive_user_no(INT32 var)		=0;
		virtual PStr	receive_user_id()				=0; //[?]���� ���������ID(�˼����������ڿ�)
		virtual void	receive_user_id(PStr var)		=0;
		virtual INT32	receive_account_no()			=0; //[4]���� ���� ���� ��ȣ(�˼�������� -1)
		virtual void	receive_account_no(INT32 var)	=0;
		virtual PStr	receive_account_id()			=0; //[?]���� ���� ���� ID(�˼����������ڿ�)
		virtual void	receive_account_id(PStr var)	=0;
		virtual INT32	receive_word_no()				=0; //[4]�������������ȣ(�˼�������� -1)
		virtual void	receive_word_no(INT32 var)		=0;
		virtual PStr	receive_word_key()				=0; //[?]������������Ű(�˼����������ڿ�)
		virtual void	receive_word_key(PStr var)		=0;
		virtual INT32	receive_character_no()			=0; //[4]��������ĳ���͹�ȣ(�˼�������� -1)
		virtual void	receive_character_no(INT32 var)	=0;
		virtual PStr	receive_character_id()			=0; //[?]��������ĳ���;��̵�(�˼����������ڿ�)
		virtual void	receive_character_id(PStr var)	=0;
		virtual PStr	send_message()					=0; //[?]�����޽���
		virtual void	send_message(PStr var)			=0;
		virtual PStr	order_id()						=0; //[?]���ӿ�������������ũ���ֹ���ȣ(World������ũ�����ʿ�)
		virtual void	order_id(PStr var)				=0;
		virtual INT32	category_no()					=0; //[4]ī�װ���ȣ
		virtual void	category_no(INT32 var)			=0;
		virtual INT32	item_no()						=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)				=0;
		virtual PStr	item_type()						=0; //[?]������Ÿ��
		virtual void	item_type(PStr var)				=0;
		virtual PStr	sale_type()						=0; //[?]�Ǹ�Ÿ��
		virtual void	sale_type(PStr var)				=0;
		virtual SHORT	order_quantity()				=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)		=0;
		virtual INT32	purchase_price()				=0;	//[4]���� �ݾ� (���η� �ִ°��� ���� ����� �ݾ�)
		virtual void	purchase_price(INT32 var)		=0;
		virtual PStr	item_sale_type()				=0; //[?]�������Ǹ�����
		virtual void	item_sale_type(PStr var)		=0;
		virtual PStr	purchase_type()					=0; //[?]����Ÿ��
		virtual void	purchase_type(PStr var)			=0;
		virtual BYTE	inventory_status()				=0; //[1]�κ��丮����(��ü���:0x1E, �Ⱦ������Ѽ���:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	attribute0()					=0; //[?]�Ӽ�
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]�Ӽ�
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]�Ӽ�
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]�Ӽ�
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]�Ӽ�
		virtual void	attribute4(PStr var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]����
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]Ŭ���̾�ƮIP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopDirectGiftItemByBindAttribute : public IResponseParent
	{
	public:
		IResponseShopDirectGiftItemByBindAttribute()			{}
		virtual ~IResponseShopDirectGiftItemByBindAttribute()	{}
		
		//get,set
		virtual INT32	total_items_count()				=0; //[4]���ֹ�����
		virtual void	total_items_count(INT32 var)	=0;
		virtual	IArrayPtr<IApprovalItem*>* items()		=0; //[?]�����۱���ü�迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 6: Shop Gift Cart Items : ����īƮ����
	class IRequestShopGiftCartItems : public IRequestParent
	{
	public:
		IRequestShopGiftCartItems()				{}
		virtual ~IRequestShopGiftCartItems()	{}
		
		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]�����Ǵ���������
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]���ӷ���
		virtual void	game_level(INT32 var)			=0;
		virtual INT32	receive_user_no()				=0; //[4]������������ڹ�ȣ(�˼�������� -1)
		virtual void	receive_user_no(INT32 var)		=0;
		virtual PStr	receive_user_id()				=0; //[?]������������ھ��̵�(�˼����������ڿ�)
		virtual void	receive_user_id(PStr var)		=0;
		virtual INT32	receive_word_no()				=0; //[4]�������������ȣ(�˼�������� -1)
		virtual void	receive_word_no(INT32 var)		=0;
		virtual PStr	receive_word_key()				=0; //[?]������������Ű(�˼����������ڿ�)
		virtual void	receive_word_key(PStr var)		=0;
		virtual INT32	receive_character_no()			=0; //[4]��������ĳ���͹�ȣ(�˼�������� -1)
		virtual void	receive_character_no(INT32 var)	=0;
		virtual PStr	receive_character_id()			=0; //[?]��������ĳ���;��̵�(�˼����������ڿ�)
		virtual void	receive_character_id(PStr var)	=0;
		virtual PStr	send_message()					=0; //[?]�����޽���
		virtual void	send_message(PStr var)			=0;
		virtual PStr	order_id()						=0; //[?]���ӿ�������������ũ���ֹ���ȣ(World������ũ�����ʿ�)
		virtual void	order_id(PStr var)				=0;
		virtual IArrayPtr<ICartItem*>* items()			=0; //[?]����īƮ���������ұ���ü�迭
		virtual BYTE	inventory_status()				=0; //[1]�κ��丮����(��ü���:0x1E, �Ⱦ������Ѽ���:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]����
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]Ŭ���̾�ƮIP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopGiftCartItems : public IResponseParent
	{
	public:
		IResponseShopGiftCartItems()			{}
		virtual ~IResponseShopGiftCartItems()	{}
		
		//get,set
		virtual INT32	total_items_count()				=0; //[?]���ֹ�����
		virtual void	total_items_count(INT32 var)	=0;
		virtual	IArrayPtr<IApprovalItem*>* items()		=0; //[?]�����۱���ü�迭
	};

//## Advanced Biling - Order : END
//#################################################################################################
//##
//#################################################################################################
//## Coupon : START
//##
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Coupon Step 1: Check Coupon : ���� üũ
	class IRequestCheckCoupon : public IRequestParent
	{
	public:
		IRequestCheckCoupon()			{}
		virtual ~IRequestCheckCoupon()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	serial()						=0; //[?]�����ø���
		virtual void	serial(PStr var)				=0;
		virtual PStr	pii()							=0;	//[?]PII
		virtual void	pii(PStr var)					=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseCheckCoupon : public IResponseParent
	{
	public:
		IResponseCheckCoupon()			{}
		virtual ~IResponseCheckCoupon()	{}

		//get,set
		virtual bool	can_use()								=0; //[1]��밡�� ����
		virtual void	can_use(bool var)						=0;
		virtual INT32	promotion_no()							=0;	//[4]���θ�� ��ȣ
		virtual void	promotion_no(INT32 var)					=0;
		virtual PStr	promotion_name()						=0;	//[?]���θ�� �̸�
		virtual void	promotion_name(PStr var)				=0;
		virtual INT64	promotion_begin_datetime()				=0; //[8]���θ�� ������
		virtual void	promotion_begin_datetime(INT64 var)		=0;
		virtual INT64	promotion_end_datetime()				=0; //[8]���θ�� ������
		virtual void	promotion_end_datetime(INT64 var)		=0;
		virtual PStr	description()							=0;	//[?]����
		virtual void	description(PStr var)					=0;
		virtual INT32	total_items_count()						=0;	//[?]���ֹ�����
		virtual void	total_items_count(INT32 var)			=0;
		virtual IArrayPtr<ICouponItem*>*	items()				=0;	//[?]���α���ü �迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Coupon Step 2: Check Coupon by Bind Attribute : ������ �ͼ� ���¿� ���� ���� üũ
	class IRequestCheckCouponByBindAttribute : public IRequestParent
	{
	public:
		IRequestCheckCouponByBindAttribute()			{}
		virtual ~IRequestCheckCouponByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����� ID(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]���� ID(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	serial()						=0; //[?]�����ø���
		virtual void	serial(PStr var)				=0;
		virtual PStr	pii()							=0;	//[?]PII
		virtual void	pii(PStr var)					=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseCheckCouponByBindAttribute : public IResponseParent
	{
	public:
		IResponseCheckCouponByBindAttribute()			{}
		virtual ~IResponseCheckCouponByBindAttribute()	{}

		//get,set
		virtual bool	can_use()								=0; //[1]��밡�� ����
		virtual void	can_use(bool var)						=0;
		virtual INT32	promotion_no()							=0;	//[4]���θ�� ��ȣ
		virtual void	promotion_no(INT32 var)					=0;
		virtual PStr	promotion_name()						=0;	//[?]���θ�� �̸�
		virtual void	promotion_name(PStr var)				=0;
		virtual INT64	promotion_begin_datetime()				=0; //[8]���θ�� ������
		virtual void	promotion_begin_datetime(INT64 var)		=0;
		virtual INT64	promotion_end_datetime()				=0; //[8]���θ�� ������
		virtual void	promotion_end_datetime(INT64 var)		=0;
		virtual PStr	description()							=0;	//[?]����
		virtual void	description(PStr var)					=0;
		virtual INT32	total_items_count()						=0;	//[?]���ֹ�����
		virtual void	total_items_count(INT32 var)			=0;
		virtual IArrayPtr<ICouponItem*>*	items()				=0;	//[?]���α���ü �迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Coupon Step 3: Use Coupon : ���� ���
	class IRequestUseCoupon : public IRequestParent
	{
	public:
		IRequestUseCoupon()				{}
		virtual ~IRequestUseCoupon()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����ھ��̵�(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	serial()						=0; //[?]�����ø���
		virtual void	serial(PStr var)				=0;
		virtual PStr	order_id()						=0; //[?]���ӿ�������������ũ���ֹ���ȣ(World������ũ�����ʿ�)
		virtual void	order_id(PStr var)				=0;
		virtual BYTE	inventory_status()				=0; //[1]�κ��丮����(��ü���:0x1E, �Ⱦ������Ѽ���:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseUseCoupon : public IResponseParent
	{
	public:
		IResponseUseCoupon()			{}
		virtual ~IResponseUseCoupon()	{}

		//get,set
		virtual INT32	total_items_count()				=0;	//[?]���ֹ�����
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IApprovalItem*>*	items()		=0;	//[?]���α���ü �迭
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Coupon Step 4: Use Coupon by Bind Attribute : ������ �ͼ� ���¿� ���� ���� ���
	class IRequestUseCouponByBindAttribute : public IRequestParent
	{
	public:
		IRequestUseCouponByBindAttribute()			{}
		virtual ~IRequestUseCouponByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]����� ��ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]����� ID(�˼����������ڿ�) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]���� ��ȣ
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]���� ID(�˼����������ڿ�) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]������ ���� ��� -1�� �����Ǹ� FCSAdapter.xml�� world_no ���� �ݿ��� : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]�������� ����Ű(�˼����������ڿ�) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���͹�ȣ(�˼����ų� �Ǵ� ����ڰ�� 0���ϰ�) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]ĳ���;��̵�(�˼����������ڿ�) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	serial()						=0; //[?]�����ø���
		virtual void	serial(PStr var)				=0;
		virtual PStr	order_id()						=0; //[?]���ӿ�������������ũ���ֹ���ȣ(World������ũ�����ʿ�)
		virtual void	order_id(PStr var)				=0;
		virtual BYTE	inventory_status()				=0; //[1]�κ��丮����(��ü���:0x1E, �Ⱦ������Ѽ���:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	callback_attribute()			=0; //[?]���Ӽ��������޵ȼӼ���
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	client_ip()						=0;	//[?]����� IP�ּ�
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseUseCouponByBindAttribute : public IResponseParent
	{
	public:
		IResponseUseCouponByBindAttribute()				{}
		virtual ~IResponseUseCouponByBindAttribute()	{}

		//get,set
		virtual INT32	total_items_count()				=0;	//[?]���ֹ�����
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IApprovalItem*>*	items()		=0;	//[?]���α���ü �迭
	};

//## Coupon : END
//#################################################################################################
//##
//#################################################################################################
//## SUB DTO : START
//##
	// ������ ����
	class IRequestItem : public IObject
	{
	public:
		IRequestItem()			{}
		virtual ~IRequestItem()	{}

		//get,set
		virtual PStr	item_key()				=0; //[?]���� ������ ���� ��
		virtual void	item_key(PStr var)		=0;
		virtual INT32	item_cost()				=0; //[4]������ ����
		virtual void	item_cost(INT32 var)	=0;
		virtual INT32	item_price()			=0; //[4]������ ���Ű���
		virtual void	item_price(INT32 var)	=0;
		virtual BYTE	sales_type()			=0;	//[1]������ ����Ÿ��
		virtual void	sales_type(BYTE var)	=0;
		virtual bool	is_trade()				=0; //[1]�ŷ����� ����(1-�ŷ�����, 0-�Ұ���)
		virtual void	is_trade(bool var)		=0;
	};

	// ������ ���� ����
	class IResponseApprovalItem : public IObject
	{
	public:
		IResponseApprovalItem()				{}
		virtual ~IResponseApprovalItem()	{}

	public:
		virtual PStr	product_key()			=0;	//[?]���� ������ ���� ��
		virtual void	product_key(PStr var)	=0;
		virtual INT32	purchase_no()			=0; //[4]���Ž��� ��ȣ
		virtual void	purchase_no(INT32 var)	=0;
	};

	
	// ������ ���� ����
	class IPurchaseItem : public IObject
	{
	public:
		IPurchaseItem()				{}
		virtual ~IPurchaseItem()	{}

	public:
		virtual INT32	product_no()			=0;	//[?]������ ��ȣ
		virtual void	product_no(INT32 var)	=0;
		virtual INT32	purchase_no()			=0; //[4]���Ž��� ��ȣ
		virtual void	purchase_no(INT32 var)	=0;
	};

	// Purchase No Structure
	class IPurchaseNo : public IObject
	{
	public:
		IPurchaseNo()			{}
		virtual ~IPurchaseNo()	{}

		//get,set
		virtual INT64	purchase_no()				=0; //[8]���Ź�ȣ
		virtual void	purchase_no(INT64 var)		=0;
	};

	// Response Purchase Item Structure : ������ ���� ���� ����
	class IResponsePurchaseItem : public IObject
	{
	public:
		IResponsePurchaseItem()				{}
		virtual ~IResponsePurchaseItem()	{}

		virtual INT32	purchase_no()					=0; //[4]���� ���ι�ȣ
		virtual void	purchase_no(INT32 var)			=0;
		virtual BYTE	purchase_status()				=0; //[1]�ֹ����� ��
		virtual void	purchase_status(BYTE var)		=0;
		virtual INT32	user_no()						=0; //[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]�����ID
		virtual void	user_id(PStr var)				=0;
		virtual PStr	product_key()					=0; //[?]���� ������ ���� ��
		virtual void	product_key(PStr var)			=0;
		virtual PStr	order_id()						=0; //[?]�ֹ���ȣ
		virtual void	order_id(PStr var)				=0;
		virtual PStr	purchase_type()					=0; //[?]����Ÿ��
		virtual void	purchase_type(PStr var)			=0;
		virtual BYTE	sales_type()					=0; //[1]�Ǹ�����
		virtual void	sales_type(BYTE var)			=0;
		virtual INT32	purchase_cost()					=0; //[4]���Ż�ǰ ����
		virtual void	purchase_cost(INT32 var)		=0;
		virtual INT32	purchase_quantity()				=0; //[4]�ֹ�����
		virtual void	purchase_quantity(INT32 var)	=0;
		virtual INT32	purchase_amount()				=0; //[4]���űݾ�
		virtual void	purchase_amount(INT32 var)		=0;
		virtual bool	is_trade()						=0; //[1]�ŷ����� ����
		virtual void	is_trade(bool var)				=0;
		virtual PStr	service_code()					=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)			=0;
		virtual INT32	world_no()						=0; //[4]�����ȣ
		virtual void	world_no(INT32 var)				=0;
		virtual INT32	character_no()					=0; //[4]ĳ���� ��ȣ
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_name()				=0; //[?]ĳ���� �̸�
		virtual void	character_name(PStr var)		=0;
		virtual INT32	game_level()					=0; //[4]���ӷ���
		virtual void	game_level(INT32 var)			=0;
		virtual INT32	receive_world_no()				=0; //[4]���� ���� �����ȣ
		virtual void	receive_world_no(INT32 var)		=0;
		virtual INT32	receive_character_no()			=0; //[4]���� ���� ĳ���� ��ȣ
		virtual void	receive_character_no(INT32 var)	=0;
		virtual PStr	receive_character_name()		=0; //[?]���� ���� ĳ���� �̸�
		virtual void	receive_character_name(PStr var)=0;
		virtual PStr	message()						=0; //[?]�޽���
		virtual void	message(PStr var)				=0;
		virtual INT64	register_datetime()				=0; //[8]�����
		virtual void	register_datetime(INT64 var)	=0;
		virtual INT64	modify_datetime()				=0; //[8]������
		virtual void	modify_datetime(INT64 var)		=0;
		virtual PStr	client_ip()						=0; //[?]����IP �ּ�
		virtual void	client_ip(PStr var)				=0;
		virtual PStr	standard_country_code()			=0; //[?]ǥ�� �����ڵ�
		virtual void	standard_country_code(PStr var)	=0;
	};

	// Response Flat Rate Payment Info Structure
	class IResponseFlatRatePaymentInfo : public IObject
	{
	public:
		IResponseFlatRatePaymentInfo()			{}
		virtual ~IResponseFlatRatePaymentInfo()	{}

		virtual INT32	use_flat_rate_no()			=0; //[4]���� ����ȣ
		virtual void	use_flat_rate_no(INT32 var)	=0;
		virtual INT32	world_no()					=0; //[4]�����ȣ
		virtual void	world_no(INT32 var)			=0;
		virtual INT64	begin_datetime()			=0; //[8]���� ��¥(Ticks)
		virtual void	begin_datetime(INT64 var)	=0;
		virtual INT64	end_datetime()				=0; //[8]���� ��¥(Ticks)
		virtual void	end_datetime(INT64 var)		=0;
		virtual PStr	use_status()				=0; //[?]����� ���� ���� (fcs_constant.h�� "Table 6 Authorization Use Status Type" ����)
		virtual void	use_status(PStr var)		=0;
	};

	// Response Coupon Item Structure : ���� ������ ����ü
	class ICouponItem : public IObject
	{
	public:
		ICouponItem()				{}
		virtual ~ICouponItem()		{}

		//get,set
		virtual PStr	service_code()				=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)		=0;
		virtual INT32	item_no()					=0; //[4]�����۹�ȣ
		virtual void	item_no(INT32 var)			=0;
		virtual PStr	item_name()					=0; //[?]�������̸�
		virtual void	item_name(PStr var)			=0;
		virtual PStr	item_code()					=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)			=0;
		virtual PStr	item_type()					=0; //[?]������Ÿ��
		virtual void	item_type(PStr var)			=0;
		virtual PStr	item_sale_type()			=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)	=0;
		virtual bool	is_include_bonus()			=0; //[1]���ʽ����Կ���
		virtual void	is_include_bonus(bool var)	=0;
		virtual INT32	item_cost()					=0; //[4]�����ۿ���
		virtual void	item_cost(INT32 var)		=0;
		virtual INT32	item_hour()					=0; //[4]�Ⱓ���������ϰ���������ȿ�Ⱓ
		virtual void	item_hour(INT32 var)		=0;
		virtual SHORT	item_quantity()				=0;	//[2]�����۱�������
		virtual void	item_quantity(SHORT var)	=0;
		virtual INT32	total_quantity()			=0; //[4]�ѱ�������
		virtual void	total_quantity(INT32 var)	=0;
		virtual SHORT	reorder_term()				=0;	//[2]���ֹ����ɽð�(0 �̸� ������)
		virtual void	reorder_term(SHORT var)		=0;
		virtual BYTE	reorder_count()				=0;	//[1]���ֹ�����Ƚ��(0 �̸� ������)
		virtual void	reorder_count(BYTE var)		=0;
		virtual PStr	attribute0()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)		=0;
		virtual PStr	attribute1()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)		=0;
		virtual PStr	attribute2()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)		=0;
		virtual PStr	attribute3()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)		=0;
		virtual PStr	attribute4()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)		=0;
	};

	// Response Coupon Item Structure : ���� ������ ����ü
	class IApprovalItem : public IObject
	{
	public:
		IApprovalItem(){}
		virtual ~IApprovalItem(){}

		//get,set
		virtual INT64	purchase_no()					=0;	//[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)			=0;
		virtual INT32	item_no()						=0;	//[4]�����۹�ȣ
		virtual void	item_no(INT32 var)				=0;
		virtual PStr	item_name()						=0; //[?]�������̸�
		virtual void	item_name(PStr var)				=0;
		virtual PStr	item_code()						=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)				=0;
		virtual SHORT	order_quantity()				=0;	//[2]�ֹ�����
		virtual void	order_quantity(SHORT var)		=0;
		virtual INT32	item_hour()						=0; //[4]�����۱Ⱓ(�ð�)
		virtual void	item_hour(INT32 var)			=0;
		virtual SHORT	item_quantity()					=0;	//[2]�����۱�������
		virtual void	item_quantity(SHORT var)		=0;
		virtual bool	is_include_bonus()				=0; //[1]���ʽ����Կ���
		virtual void	is_include_bonus(bool var)		=0;
	};

	// Response Cart Item Structure
	class ICartItemInfo : public IObject
	{
	public:
		ICartItemInfo()				{}
		virtual ~ICartItemInfo()	{}

		//get,set
		virtual INT64	cart_no()					=0; //[8]īƮ��ȣ
		virtual void	cart_no(INT64 var)			=0;
		virtual PStr	service_code()				=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)		=0;
		virtual INT32	category_no()				=0; //[4]ī�װ���ȣ
		virtual void	category_no(INT32 var)		=0;
		virtual INT32	item_no()					=0; //[4]�����۹�ȣ
		virtual void	item_no(INT32 var)			=0;
		virtual PStr	item_name()					=0; //[?]�������̸�
		virtual void	item_name(PStr var)			=0;
		virtual PStr	item_code()					=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)			=0;
		virtual PStr	item_type()					=0; //[?]������Ÿ��
		virtual void	item_type(PStr var)			=0;
		virtual PStr	sale_type()					=0; //[?]�Ǹ�Ÿ��
		virtual void	sale_type(PStr var)			=0;
		virtual PStr	item_sale_type()			=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)	=0;
		virtual bool	is_include_bonus()			=0; //[1]���ʽ����Կ���
		virtual void	is_include_bonus(bool var)	=0;
		virtual INT32	item_cost()					=0; //[4]�����ۿ���
		virtual void	item_cost(INT32 var)		=0;
		virtual INT32	item_hour()					=0; //[4]�Ⱓ���������ϰ���������ȿ�Ⱓ
		virtual void	item_hour(INT32 var)		=0;
		virtual SHORT	item_quantity()				=0;	//[2]�����۱�������
		virtual void	item_quantity(SHORT var)	=0;
		virtual INT32	total_quantity()			=0; //[4]�ѱ�������
		virtual void	total_quantity(INT32 var)	=0;
		virtual SHORT	reorder_term()				=0;	//[2]���ֹ����ɽð�(0 �̸� ������)
		virtual void	reorder_term(SHORT var)		=0;
		virtual BYTE	reorder_count()				=0;	//[1]���ֹ�����Ƚ��(0 �̸� ������)
		virtual void	reorder_count(BYTE var)		=0;
		virtual INT32	user_no()					=0;	//[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)			=0;
		virtual PStr	user_id()					=0; //[?]����ھ��̵�
		virtual void	user_id(PStr var)			=0;
		virtual SHORT	order_quantity()			=0;	//[2]�ֹ�����
		virtual void	order_quantity(SHORT var)	=0;
		virtual INT32	world_no()					=0;	//[4]�����ȣ
		virtual void	world_no(INT32 var)			=0;
		virtual PStr	world_key()					=0; //[?]����Ű
		virtual void	world_key(PStr var)			=0;
		virtual INT32	chracter_no()				=0;	//[4]ĳ���͹�ȣ
		virtual void	chracter_no(INT32 var)		=0;
		virtual PStr	chracter_id()				=0; //[?]ĳ���;��̵�
		virtual void	chracter_id(PStr var)		=0;
		virtual INT64	modify_datetime()			=0; //[8]�����Ͻ�
		virtual void	modify_datetime(INT64 var)	=0;
		virtual PStr	attribute0()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)		=0;
		virtual PStr	attribute1()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)		=0;
		virtual PStr	attribute2()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)		=0;
		virtual PStr	attribute3()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)		=0;
		virtual PStr	attribute4()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)		=0;
		virtual PStr	description()				=0; //[?]����
		virtual void	description(PStr var)		=0;
		virtual INT32	sale_price()				=0;	//[4]�ǸŰ�
		virtual void	sale_price(INT32 var)		=0;
		virtual PStr	discount_type()				=0; //[?]��������
		virtual void	discount_type(PStr var)		=0;
		virtual INT32	discount_price()			=0;	//[4]���αݾ�
		virtual void	discount_price(INT32 var)	=0;
		virtual BYTE	discount_rate()				=0;	//[1]������(%)
		virtual void	discount_rate(BYTE var)		=0;
		virtual INT32	flat_price()				=0;	//[4]��������
		virtual void	flat_price(INT32 var)		=0;
	};
	
	// Request Register Item Structure : item ��� 
	class IRegisterItem : public IObject
	{
	public:
		IRegisterItem()				{}
		virtual ~IRegisterItem()		{}

		//get,set
		virtual INT32	category_no()					=0; //[4]ī�װ���ȣ
		virtual void	category_no(INT32 var)			=0;
		virtual INT32	item_no()						=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)				=0;
		virtual SHORT	purchase_quantity()				=0; //[2]���ż���
		virtual void	purchase_quantity(SHORT var)	=0;
		virtual PStr	attribute0()					=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)			=0;
	};

	// Request Item Structure
	class ICartItem : public IObject
	{
	public:
		ICartItem()				{}
		virtual ~ICartItem()	{}

		//get,set
		virtual INT64	cart_no()					=0; //[8]īƮ��ȣ
		virtual void	cart_no(INT64 var)			=0;
		virtual PStr	sale_type()					=0; //[?]�Ǹ�����
		virtual void	sale_type(PStr var)			=0;
		virtual PStr	discount_type()				=0; //[4]��������
		virtual void	discount_type(PStr var)		=0;
		virtual INT32	item_no()					=0; //[4]�����۹�ȣ
		virtual void	item_no(INT32 var)			=0;
		virtual PStr	item_sale_type()			=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)	=0;
		virtual PStr	item_type()					=0; //[?]����������
		virtual void	item_type(PStr var)			=0;
		virtual INT32	purchase_price()			=0; //[4]�ǸŰ�
		virtual void	purchase_price(INT32 var)	=0;
		virtual PStr	purchase_type()				=0; //[?]�Ǹ�Ÿ��
		virtual void	purchase_type(PStr var)		=0;
	};

	// Request No
	class IRequestNo : public IObject
	{
	public:
		IRequestNo()			{}
		virtual ~IRequestNo()	{}

		//get,set
		virtual INT64	no()			=0; //[8]īƮ/���ø���Ʈ ��ȣ
		virtual void	no(INT64 var)	=0;
	};

	// Response Wish Item
	class IWishItemInfo : public IObject
	{
	public:
		IWishItemInfo()				{}
		virtual ~IWishItemInfo()	{}

		//get,set
		virtual INT64	wish_no()					=0; //[8]Wish ��ȣ
		virtual void	wish_no(INT64 var)			=0;
		virtual PStr	service_code()				=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)		=0;
		virtual INT32	category_no()				=0; //[4]ī�װ���ȣ
		virtual void	category_no(INT32 var)		=0;
		virtual INT32	item_no()					=0; //[4]�����۹�ȣ
		virtual void	item_no(INT32 var)			=0;
		virtual PStr	item_name()					=0; //[?]�������̸�
		virtual void	item_name(PStr var)			=0;
		virtual PStr	item_code()					=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)			=0;
		virtual PStr	item_type()					=0; //[?]������Ÿ��
		virtual void	item_type(PStr var)			=0;
		virtual PStr	sale_type()					=0; //[?]�Ǹ�Ÿ��
		virtual void	sale_type(PStr var)			=0;
		virtual PStr	item_sale_type()			=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)	=0;
		virtual INT32	item_cost()					=0; //[4]�����ۿ���
		virtual void	item_cost(INT32 var)		=0;
		virtual INT32	item_hour()					=0; //[4]�Ⱓ���������ϰ���������ȿ�Ⱓ
		virtual void	item_hour(INT32 var)		=0;
		virtual SHORT	item_quantity()				=0;	//[2]�����۱�������
		virtual void	item_quantity(SHORT var)	=0;
		virtual INT32	total_quantity()			=0; //[4]�ѱ�������
		virtual void	total_quantity(INT32 var)	=0;
		virtual SHORT	reorder_term()				=0;	//[2]���ֹ����ɽð�(0 �̸� ������)
		virtual void	reorder_term(SHORT var)		=0;
		virtual BYTE	reorder_count()				=0;	//[1]���ֹ�����Ƚ��(0 �̸� ������)
		virtual void	reorder_count(BYTE var)		=0;
		virtual INT32	user_no()					=0;	//[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)			=0;
		virtual PStr	user_id()					=0; //[?]����ھ��̵�
		virtual void	user_id(PStr var)			=0;
		virtual INT32	world_no()					=0;	//[4]�����ȣ
		virtual void	world_no(INT32 var)			=0;
		virtual PStr	world_key()					=0; //[?]����Ű
		virtual void	world_key(PStr var)			=0;
		virtual INT32	chracter_no()				=0;	//[4]ĳ���͹�ȣ
		virtual void	chracter_no(INT32 var)		=0;
		virtual PStr	chracter_id()				=0; //[?]ĳ���;��̵�
		virtual void	chracter_id(PStr var)		=0;
		virtual INT64	modify_datetime()			=0; //[8]�����Ͻ�
		virtual void	modify_datetime(INT64 var)	=0;
		virtual PStr	description()				=0; //[?]����
		virtual void	description(PStr var)		=0;
	};

	// Response Cash Inventory Items Structure
	// Cash Inventory Items Structure
	class ICashInventoryItems : public IObject
	{
	public:
		ICashInventoryItems()			{}
		virtual ~ICashInventoryItems()	{}

		//get,set
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual PStr	purchase_guid()						=0; //[?]�ֹ����� ��
		virtual void	purchase_guid(PStr var)				=0;
		virtual INT32	user_no()							=0; //[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]�����ID
		virtual void	user_id(PStr var)					=0;
		virtual PStr	service_code()						=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]�����ȣ
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]����Ű
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���� ��ȣ
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���� �̸�
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]�������̸�
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]����������
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)			=0;
		virtual bool	is_include_bonus()					=0; //[1]���ʽ���ǰ��������
		virtual void	is_include_bonus(bool var)			=0;
		virtual bool	is_gift()							=0; //[1]��������
		virtual void	is_gift(bool var)					=0;
		virtual SHORT	order_quantity()					=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]��������
		virtual void	remain_quantity(SHORT var)			=0;
		virtual INT64	first_receive_datetime()			=0; //[8]ó�����ɽð� (C#�� Tick)
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]�������ɽð� (C#�� Tick)
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT32	sender_user_no()					=0; //[4]���������ȣ
		virtual void	sender_user_no(INT32 var)			=0;
		virtual PStr	sender_user_id()					=0; //[?]����������̵�
		virtual void	sender_user_id(PStr var)			=0;
		virtual INT32	sender_world_no()					=0; //[4]���������ȣ
		virtual void	sender_world_no(INT32 var)			=0;
		virtual PStr	sender_world_key()					=0; //[?]��������Ű
		virtual void	sender_world_key(PStr var)			=0;
		virtual INT32	sender_character_no()				=0; //[4]����ĳ���͹�ȣ
		virtual void	sender_character_no(INT32 var)		=0;
		virtual PStr	sender_character_id()				=0; //[?]����ĳ���� Id
		virtual void	sender_character_id(PStr var)		=0;
		virtual PStr	send_message()						=0; //[?]�޽���
		virtual void	send_message(PStr var)				=0;
		virtual SHORT	inventory_keep_days()				=0; //[2]�κ��丮�����Ⱓ
		virtual void	inventory_keep_days(SHORT var)		=0;
		virtual SHORT	item_quantity()						=0; //[2]��������
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]���Ⱓ
		virtual void	item_hour(INT32 var)				=0;
		virtual INT64	register_datetime()					=0; //[8]��Ͻð� (C#�� Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]��ǰ����
		virtual void	description(PStr var)				=0;
	};

	// Cash Inventory Package Items Structure
	class IPackageItem : public IObject
	{
	public:
		IPackageItem()			{}
		virtual ~IPackageItem()	{}

		//get,set
		virtual INT64	package_inventory_no()				=0; //[8] ��Ű���κ��丮��ȣ
		virtual void	package_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]�����ID
		virtual void	user_id(PStr var)					=0;
		virtual PStr	service_code()						=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]�����ȣ
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]����Ű
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���� ��ȣ
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���� �̸�
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]�������̸�
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]����������
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]��������
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]���Ⱓ
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]�������
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]��������
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]�κ��丮�����ϼ�
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]ó�������ð�(C#�� Tick)
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]�������ɽð�(C#�� Tick)
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]��Ͻð� (C#�� Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]��ǰ����
		virtual void	description(PStr var)				=0;
	};

	// Cash Inventory Lottery Items Structure
	class ILotteryItem : public IObject
	{
	public:
		ILotteryItem()			{}
		virtual ~ILotteryItem()	{}

		//get,set
		virtual INT64	lottery_inventory_no()				=0; //[8]�����κ��丮���丮��ȣ
		virtual void	lottery_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ��κ��丮��ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]�����ID
		virtual void	user_id(PStr var)					=0;
		virtual PStr	service_code()						=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]�����ȣ
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]����Ű
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���� ��ȣ
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���� �̸�
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]�������̸�
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]����������
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]��������
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]���Ⱓ
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]�������
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]��������
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]�κ��丮�����ϼ�
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]ó�������ð�(C#�� Tick)
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]�������ɽð�(C#�� Tick)
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]��Ͻð� (C#�� Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]��ǰ����
		virtual void	description(PStr var)				=0;
	};
	
	// Cash Inventory Bonus Items Structure
	class IBonusItem : public IObject
	{
	public:
		IBonusItem()			{}
		virtual ~IBonusItem()	{}

		//get,set
		virtual INT64	bonus_inventory_no()				=0; //[8]���ʽ��κ��丮��ȣ
		virtual void	bonus_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ��κ��丮��ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]�����ID
		virtual void	user_id(PStr var)					=0;
		virtual PStr	service_code()						=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]�����ȣ
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]����Ű
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���� ��ȣ
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���� �̸�
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]�������̸�
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]����������
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]��������
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]���Ⱓ
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]�������
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]��������
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]�κ��丮�����ϼ�
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]ó�������ð�(C#�� Tick)
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]�������ɽð�(C#�� Tick)
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]��Ͻð� (C#�� Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]��ǰ����
		virtual void	description(PStr var)				=0;
	};

	// Response Cash Inventory Items Structure by Bind Attribute
	// Cash Inventory Items Structure by Bind Attribute
	class ICashInventoryItemsByBindAttribute : public IObject
	{
	public:
		ICashInventoryItemsByBindAttribute()			{}
		virtual ~ICashInventoryItemsByBindAttribute()	{}

		//get,set
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual PStr	purchase_guid()						=0; //[?]�ֹ����� ��
		virtual void	purchase_guid(PStr var)				=0;
		virtual INT32	user_no()							=0; //[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]�����ID
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]���� ID
		virtual void	account_id(PStr var)				=0;
		virtual PStr	service_code()						=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]�����ȣ
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]����Ű
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���� ��ȣ
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���� �̸�
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]�������̸�
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]����������
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)			=0;
		virtual bool	is_include_bonus()					=0; //[1]���ʽ���ǰ��������
		virtual void	is_include_bonus(bool var)			=0;
		virtual bool	is_gift()							=0; //[1]��������
		virtual void	is_gift(bool var)					=0;
		virtual SHORT	order_quantity()					=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]�������� : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	remain_quantity(SHORT var)			=0;
		virtual INT64	first_receive_datetime()			=0; //[8]ó�����ɽð� (C#�� Tick) : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]�������ɽð� (C#�� Tick) : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT32	sender_user_no()					=0; //[4]���������ȣ
		virtual void	sender_user_no(INT32 var)			=0;
		virtual PStr	sender_user_id()					=0; //[?]����������̵�
		virtual void	sender_user_id(PStr var)			=0;
		virtual INT32	sender_account_no()					=0; //[4]���� ���� ��ȣ
		virtual void	sender_account_no(INT32 var)		=0;
		virtual PStr	sender_account_id()					=0; //[?]���� ���� ID
		virtual void	sender_account_id(PStr var)			=0;
		virtual INT32	sender_world_no()					=0; //[4]���������ȣ
		virtual void	sender_world_no(INT32 var)			=0;
		virtual PStr	sender_world_key()					=0; //[?]��������Ű
		virtual void	sender_world_key(PStr var)			=0;
		virtual INT32	sender_character_no()				=0; //[4]����ĳ���͹�ȣ
		virtual void	sender_character_no(INT32 var)		=0;
		virtual PStr	sender_character_id()				=0; //[?]����ĳ���� Id
		virtual void	sender_character_id(PStr var)		=0;
		virtual PStr	send_message()						=0; //[?]�޽���
		virtual void	send_message(PStr var)				=0;
		virtual SHORT	inventory_keep_days()				=0; //[2]�κ��丮�����Ⱓ
		virtual void	inventory_keep_days(SHORT var)		=0;
		virtual SHORT	item_quantity()						=0; //[2]��������
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]���Ⱓ
		virtual void	item_hour(INT32 var)				=0;
		virtual INT64	register_datetime()					=0; //[8]��Ͻð� (C#�� Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]��ǰ����
		virtual void	description(PStr var)				=0;
	};

	
	// Cash Inventory Package Items Structure by Bind Attribute
	class IPackageItemByBindAttribute : public IObject
	{
	public:
		IPackageItemByBindAttribute()			{}
		virtual ~IPackageItemByBindAttribute()	{}

		//get,set
		virtual INT64	package_inventory_no()				=0; //[8] ��Ű���κ��丮��ȣ
		virtual void	package_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ���ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]�����ID
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]���� ID
		virtual void	account_id(PStr var)				=0;
		virtual PStr	service_code()						=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]�����ȣ
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]����Ű
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���� ��ȣ
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���� �̸�
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]�������̸�
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]����������
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]��������
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]���Ⱓ
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]�������
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]�������� : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]�κ��丮�����ϼ�
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]ó�������ð�(C#�� Tick) : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]�������ɽð�(C#�� Tick) : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]��Ͻð� (C#�� Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]��ǰ����
		virtual void	description(PStr var)				=0;
	};

	// Cash Inventory Lottery Items Structure by Bind Attribute
	class ILotteryItemByBindAttribute : public IObject
	{
	public:
		ILotteryItemByBindAttribute()			{}
		virtual ~ILotteryItemByBindAttribute()	{}

		//get,set
		virtual INT64	lottery_inventory_no()				=0; //[8]�����κ��丮���丮��ȣ
		virtual void	lottery_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ��κ��丮��ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]�����ID
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]���� ID
		virtual void	account_id(PStr var)				=0;
		virtual PStr	service_code()						=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]�����ȣ
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]����Ű
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���� ��ȣ
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���� �̸�
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]�������̸�
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]����������
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]��������
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]���Ⱓ
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]�������
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]�������� : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]�κ��丮�����ϼ�
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]ó�������ð�(C#�� Tick) : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]�������ɽð�(C#�� Tick) : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]��Ͻð� (C#�� Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]��ǰ����
		virtual void	description(PStr var)				=0;
	};
	
	// Cash Inventory Bonus Items Structure by Bind Attribute
	class IBonusItemByBindAttribute : public IObject
	{
	public:
		IBonusItemByBindAttribute()				{}
		virtual ~IBonusItemByBindAttribute()	{}

		//get,set
		virtual INT64	bonus_inventory_no()				=0; //[8]���ʽ��κ��丮��ȣ
		virtual void	bonus_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]�ֹ��κ��丮��ȣ
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]����ڹ�ȣ
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]�����ID
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0; //[4]���� ��ȣ
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]���� ID
		virtual void	account_id(PStr var)				=0;
		virtual PStr	service_code()						=0; //[?]�����ڵ�
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]�����ȣ
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]����Ű
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]ĳ���� ��ȣ
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]ĳ���� �̸�
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]�����۰�����ȣ
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]�������̸�
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]����������
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]�������Ǹ�Ÿ��
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]��������
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]���Ⱓ
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]�������
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]�ֹ�����
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]�������� : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]�κ��丮�����ϼ�
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]ó�������ð�(C#�� Tick) : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]�������ɽð�(C#�� Tick) : Advanced Billing - Cash Inventory �� Step 12. ������ ��� �� ��
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]��Ͻð� (C#�� Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]Ȯ��Ӽ�
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]��ǰ����
		virtual void	description(PStr var)				=0;
	};

	// 
	class IPickupStandbyCashInventoryItem : public IObject
	{
	public:
		IPickupStandbyCashInventoryItem()			{}
		virtual ~IPickupStandbyCashInventoryItem()	{}

		//get,set
		virtual BYTE	item_expand_flag()			=0; //[1]Cash Inventory Item Expand Flags (fcs_constant.h�� "Table 11 Inquiry Cash Inventory Expand Flags" ����)
		virtual void	item_expand_flag(BYTE var)	=0;
		virtual INT32	item_no()					=0;	//[4]�������ڵ�
		virtual void	item_no(INT32 var)			=0;
		virtual PStr	item_code()					=0; //[?]���Ӿ����۰����ڵ�
		virtual void	item_code(PStr var)			=0;
		virtual PStr	item_type()					=0; //[?]����������
		virtual void	item_type(PStr var)			=0;
		virtual SHORT	item_quantity()				=0; //[2]��������
		virtual void	item_quantity(SHORT var)	=0;
		virtual INT32	item_hour()					=0; //[4]���Ⱓ
		virtual void	item_hour(INT32 var)		=0;
		virtual	PStr	attribute0()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute0(PStr var)		=0;
		virtual	PStr	attribute1()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute1(PStr var)		=0;
		virtual	PStr	attribute2()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute2(PStr var)		=0;
		virtual	PStr	attribute3()				=0; //[?]Ȯ��Ӽ�
		virtual void	attribute3(PStr var)		=0;

	};

	// Use Storage STItemProperty Structure
	class ISTItemProperty : public IObject
	{
	public:
		ISTItemProperty()			{}
		virtual ~ISTItemProperty()	{}

		//get,set
		virtual INT32	property_seq()			=0; //[4]�Ӽ� ��ȣ
		virtual void	property_seq(INT32 var)	=0;
		virtual INT32	value()					=0; //[4]�Ӽ� ��
		virtual void	value(INT32 var)		=0;
	};

	// Jewel Balance Item Structure
	class IJewelBalanceItem : public IObject
	{
	public :
		IJewelBalanceItem()			{}
		virtual ~IJewelBalanceItem()	{}

		virtual	INT32	cash_type()				=0; //[?]ȭ�� ��������  (Table 18 Cash Type)
		virtual void	cash_type(INT32 var)	=0;
		virtual INT64	coin()					=0; //[8]�ܾ�
		virtual void	coin(INT64 var)			=0;
	};

	// WShop
	class IPStrA : public IObject
	{
	public :
		IPStrA()			{}
		virtual ~IPStrA()	{}

		virtual PStr	value()							    =0; //[?]���ڿ�
		virtual void	value(PStr var)						=0;
	};

	class IWShopRequestPurchaseItem : public IObject
	{
	public:
		IWShopRequestPurchaseItem()				{}
		virtual ~IWShopRequestPurchaseItem()	{}

	public:
		virtual INT32	item_sale_no() =0; //[4] ������ �Ǹ� ��ȣ
		virtual void	item_sale_no(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT32	purchase_price() =0; //[4] ���� �ݾ� (���η� �ִ°��� ���� ����� �ݾ�)
		virtual void	purchase_price(INT32 var) = 0;
		virtual SHORT	order_quantity() =0; //[2] �ֹ�����
		virtual void	order_quantity(SHORT var) = 0;
		virtual PStr	attribute0() =0; //[?] �Ӽ� (Ŭ����� Property0) : optional
		virtual void	attribute0(PStr var) = 0;
		virtual PStr	attribute1() =0; //[?] �Ӽ� (Ŭ����� Property1) : optional
		virtual void	attribute1(PStr var) = 0;
		virtual PStr	attribute2() =0; //[?] �Ӽ� (Ŭ����� Property2) : optional
		virtual void	attribute2(PStr var) = 0;
		virtual PStr	attribute3() =0; //[?] �Ӽ� (Ŭ����� Property3) : optional
		virtual void	attribute3(PStr var) = 0;
		virtual PStr	attribute4() =0; //[?] �Ӽ� (Ŭ����� Property4) : optional
		virtual void	attribute4(PStr var) = 0;
		virtual PStr	description() =0; //[?] ���� : optional
		virtual void	description(PStr var) = 0;
	};

	class IWShopResponseApproval : public IObject
	{
	public :
		IWShopResponseApproval()			{}
		virtual ~IWShopResponseApproval()	{}

		virtual INT32	item_sale_no() =0; //[4] ������ �Ǹ� ��ȣ
		virtual void	item_sale_no(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] �ֹ���ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT64	purchase_no() =0; //[8] ���� �� �߱޵� ���Ź�ȣ
		virtual void	purchase_no(INT64 var) = 0;
		virtual PStr	item_code() =0; //[?] ������ �ڵ�
		virtual void	item_code(PStr var) = 0;
		virtual INT32	item_minute() =0; //[4] ������ ��ȿ ��� �Ⱓ(��)
		virtual void	item_minute(INT32 var) = 0;
		virtual SHORT	order_quantity() =0; //[2] �ֹ�����
		virtual void	order_quantity(SHORT var) = 0;
		virtual PStr	attribute0() =0; //[?] �Ӽ� (Ŭ����� Property0)
		virtual void	attribute0(PStr var) = 0;
		virtual PStr	attribute1() =0; //[?] �Ӽ� (Ŭ����� Property1)
		virtual void	attribute1(PStr var) = 0;
		virtual PStr	attribute2() =0; //[?] �Ӽ� (Ŭ����� Property2)
		virtual void	attribute2(PStr var) = 0;
		virtual PStr	attribute3() =0; //[?] �Ӽ� (Ŭ����� Property3)
		virtual void	attribute3(PStr var) = 0;
		virtual PStr	attribute4() =0; //[?] �Ӽ� (Ŭ����� Property4)
		virtual void	attribute4(PStr var) = 0;
	};

	class IWShopRequestOrderId : public IObject
	{
	public :
		IWShopRequestOrderId()			{}
		virtual ~IWShopRequestOrderId()	{}

		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
	};

	class IWShopInventoryItem : public IObject
	{
	public :
		IWShopInventoryItem()			{}
		virtual ~IWShopInventoryItem()	{}

		virtual PStr	purchase_order_id() =0; //[?] �� ������ ���� �� ���Ǿ��� ���� �� �ֹ� ��ȣ
		virtual void	purchase_order_id(PStr var) = 0;
		virtual INT64	purchase_no() =0; //[8] �������� ���� ����� ������ ���� ��ȣ
		virtual void	purchase_no(INT64 var) = 0;
		virtual INT32	item_no() =0; //[4] �������� ��ȣ
		virtual void	item_no(INT32 var) = 0;
		virtual PStr	item_code() =0; //[?] ���ӿ��� �����ϰ� �ִ� ������ �ڵ� ��
		virtual void	item_code(PStr var) = 0;
		virtual INT32	item_minute() =0; //[4] �������� ��ȿ ��� �Ⱓ (��)
		virtual void	item_minute(INT32 var) = 0;
		virtual SHORT	item_quantity() =0; //[2] ������ ����
		virtual void	item_quantity(SHORT var) = 0;
		virtual INT64	register_date_time() =0; //[8] �� �������� �κ��丮�� ��ϵ� �Ͻ�
		virtual void	register_date_time(INT64 var) = 0;
		virtual INT32	inventory_keep_days() =0; //[4] �κ��丮 ���� ���� �Ⱓ (��)
		virtual void	inventory_keep_days(INT32 var) = 0;
		virtual bool	is_gift() =0; //[1] (���� ������) ���� ����
		virtual void	is_gift(bool var) = 0;
		virtual INT32	sender_user_no() =0; //[4] (Is Gift�� ���� ��) ���� ���� ����� ��ȣ
		virtual void	sender_user_no(INT32 var) = 0;
		virtual PStr	sender_user_id() =0; //[?] (Is Gift�� ���� ��) ���� ���� ����� ���̵�
		virtual void	sender_user_id(PStr var) = 0;
		virtual INT32	sender_account_no() =0; //[4] (Is Gift�� ���� ��) ���� ���� ���� ��ȣ
		virtual void	sender_account_no(INT32 var) = 0;
		virtual PStr	sender_account_id() =0; //[?] (Is Gift�� ���� ��) ���� ���� ���� ���̵�
		virtual void	sender_account_id(PStr var) = 0;
		virtual PStr	sender_world_key() =0; //[?] (Is Gift�� ���� ��)  ���� ���� ���� Ű
		virtual void	sender_world_key(PStr var) = 0;
		virtual INT64	sender_character_no() =0; //[8] (Is Gift�� ���� ��)  ���� ���� ĳ���� ��ȣ
		virtual void	sender_character_no(INT64 var) = 0;
		virtual PStr	sender_character_id() =0; //[?] (Is Gift�� ���� ��) ���� ���� ĳ���� ��
		virtual void	sender_character_id(PStr var) = 0;
		virtual PStr	send_message() =0; //[?] (Is Gift�� ���� ��) ���� �޽���
		virtual void	send_message(PStr var) = 0;
	};

	class IWShopPickUpItem : public IObject
	{
	public :
		IWShopPickUpItem()			{}
		virtual ~IWShopPickUpItem()	{}

		virtual PStr	order_id() =0; //[?] ���� ���ۿ� ���� ���� �� �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT64	purchase_no() =0; //[8] �� �����ۿ� ���� ���� ��ȣ
		virtual void	purchase_no(INT64 var) = 0;
		virtual PStr	item_code() =0; //[?] ������ �ڵ�
		virtual void	item_code(PStr var) = 0;
		virtual INT32	item_minute() =0; //[4] ������ �Ⱓ (��)
		virtual void	item_minute(INT32 var) = 0;
		virtual SHORT	item_quantity() =0; //[2] ���� ������ ����
		virtual void	item_quantity(SHORT var) = 0;
	};

	class IWShopResponseOrderStatus : public IObject
	{
	public :
		IWShopResponseOrderStatus()				{}
		virtual ~IWShopResponseOrderStatus()	{}

		virtual PStr	order_id() =0; //[?] ���ӿ��� ������ ����ũ�� �ֹ� ��ȣ
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] ���� �ֹ� ���� (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};

//## SUB DTO : END
//#################################################################################################

} // namespace

#endif