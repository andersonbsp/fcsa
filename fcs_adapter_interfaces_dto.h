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

	// 모든 인터페이스가 상속하는 상위 인터페이스
	class IObject
	{
	public:
		IObject(){}
		virtual ~IObject(){}
	public:
		virtual void release()				=0;	// 자원해제 필수
		virtual const wchar_t* toString()	=0;	// 디버깅용
	};
	
	// DTO 의 sub DTO 를 담는 배열 클래스
	template<typename T>
	class IArrayPtr
	{
	public:
		IArrayPtr(){}
		virtual ~IArrayPtr(){}

		// sub DTO 추가 후 리턴
		// sub DTO는 자신을 포함한 DTO와 같은 생명주기를 갖음.
		// 즉, DTO가 release() 될때 IArrayPtr에 등록되어있는 DTO들도 release()됨
		virtual T add()			=0;		
		virtual INT32 size()	=0;		// 현재 사이즈
		virtual bool empty()	=0;		// 비어있는지 여부
		virtual T at(INT32 i)	=0;		// 해당 위치 객체 리턴(없는 경우 NULL)
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Request, Response interface 조상
	class IRequestResponseParent : public IObject
	{
	public:
		IRequestResponseParent()			{}
		virtual ~IRequestResponseParent()	{}

		virtual BYTE	reserved_character()			=0;	//[1]0xFF
	//	virtual void	reserved_character(BYTE var)	=0;
		virtual INT32	packet_length()					=0;	//[4]전체 Packet 길이 (헤더길이 5bytes 제외)
	//	virtual void	packet_length(INT32 var)		=0;
		virtual BYTE	packet_type()					=0;	//[1]Packet 형식
	//	virtual void	packet_type(BYTE var)			=0;
		virtual INT32	transaction_id()				=0;	//[4]클라이언트에서 전달하는 주문번호
		virtual void	transaction_id(INT32 var)		=0;	//sync 통신시 중요한 값

		//[기능]
		virtual void	clear(bool parent=true)			=0;	// 데이터 멤버 초기화. false를 줄경우 부모 class의 데이터 멤버는 초기화 하지 않는다.
	};

	class IRequestParent : public IRequestResponseParent
	{
	public:
		IRequestParent()			{}
		virtual ~IRequestParent()	{}
	
		virtual INT32	issue_transaction_id()		=0;	// 현재 dto에 transaction_id 재발급
	};

	class IResponseParent : public IRequestResponseParent
	{
	public:
		IResponseParent()			{}
		virtual ~IResponseParent()	{}

		virtual INT32	result_code()				=0;	//[4]로직 결과 값 : fcsa::kRCSuccess 인 경우 정상(fcs_constant.h 참조)
		virtual void	result_code(INT32 var)		=0;
		virtual BYTE	condition_type()			=0;	//[1]FCS 서버 상태 : fcsa::kCT_Running 인 경우 정상(fcs_constant.h 참조)
		virtual void	condition_type(BYTE var)	=0;

		// [기능]
		// result_code(), condition_type() 정상여부 체크 (fcs_constant.h 참조)
		// resulce_code 이 kRCSuccess 이고 condition_type 이 kCT_Running 인 경우 true 리턴
		virtual bool	isSuccess()					=0;
		// [기능]
		// response의 Extension 항목에 json 포맷을 사용한다고 표기되어 있을 경우 사용함
		// extension : Response 중 extension() 항목
		// key : json의 key값
		// default_value : json parsing이 실패 했을 경우 return 값으로 받기 원하는 값
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

		virtual PStr	service_code()						=0;	//[?]서비스 코드
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0;	//[4]월드번호
		virtual void	world_no(INT32 var)					=0;
		virtual INT32	client_keep_alive_period()			=0;	//[4]연결유지 시간 (0이하 또는 0x7FFFFFFF이면 서버에서 체크를 하지 않는다.)
		virtual void	client_keep_alive_period(INT32 var)	=0;
	};

	class IResponseInitialize : public IResponseParent
	{
	public:
		IResponseInitialize()			{}
		virtual ~IResponseInitialize()	{}

		virtual PStr	service_code()			=0;	//[?]서비스코드
		virtual void	service_code(PStr var)	=0;
		virtual INT32	world_no()				=0;	//[4]월드번호
		virtual void	world_no(INT32 var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Common Step 2: Keep Alive
	class IRequestKeepAlive : public IRequestParent
	{
	public:
		IRequestKeepAlive()				{}
		virtual ~IRequestKeepAlive()	{}

		virtual INT64	caching_product_version()			=0;	//[8]상품 리스트 정보 Hash Code 값
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
	// Authentication & Authorization Step 1: Game Login : 게임 로그인
	class IRequestGameLogin : public IRequestParent
	{
	public:
		IRequestGameLogin()				{}
		virtual ~IRequestGameLogin()	{}

		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	authentication_key()			=0;	//[?]인증키
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseGameLogin : public IResponseParent
	{
	public:
		IResponseGameLogin()			{}
		virtual ~IResponseGameLogin()	{}

		virtual bool										is_flat_rate_user()					=0; //[1]정액유저 여부
		virtual void										is_flat_rate_user(bool var)			=0;
		virtual PStr										user_type()							=0; //[?]유저구분. (fcs_constant.h의 "Table 7 Authorization User Type" 참조)
		virtual void										user_type(PStr var)					=0;
		virtual IArrayPtr<IResponseFlatRatePaymentInfo*>*	structure_array()					=0; //[?]활성화된 정액상품 구조체 배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 2: Game Logout : 게임 로그아웃
	class IRequestGameLogout : public IRequestParent
	{
	public:
		IRequestGameLogout()			{}
		virtual ~IRequestGameLogout()	{}

		virtual INT32	user_no()			=0; //[4]사용자 번호
		virtual void	user_no(INT32 var)	=0;
		virtual PStr	client_ip()			=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)	=0;
	};

	class IResponseGameLogout : public IResponseParent
	{
	public:
		IResponseGameLogout()			{}
		virtual ~IResponseGameLogout()	{}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 3: Premium Service Expired Callback : 프리미엄 서비스 기간 만료

	class IResponsePremiumServiceExpiredCallback : public IResponseParent
	{
	public:
		IResponsePremiumServiceExpiredCallback()			{}
		virtual ~IResponsePremiumServiceExpiredCallback()	{}

		virtual INT32	user_no()			=0; //[4]사용자 번호
		virtual void	user_no(INT32 var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 4: Force User Logout Callback : 강제 로그아웃
	class IResponseForceUserLogoutCallback : public IResponseParent
	{
	public:
		IResponseForceUserLogoutCallback()			{}
		virtual ~IResponseForceUserLogoutCallback()	{}

		virtual INT32	user_no()				=0; //[4]사용자 번호
		virtual void	user_no(INT32 var)		=0;
		virtual PStr	description()			=0; //[?]설명
		virtual void	description(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 5: Request Authentication Key : 인증키 요청
	class IRequestAuthenticationKey : public IRequestParent
	{
	public:
		IRequestAuthenticationKey()				{}
		virtual ~IRequestAuthenticationKey()	{}

		virtual INT32		user_no()			=0; //[4]사용자 번호
		virtual void		user_no(INT32 var)	=0;
		virtual PStr		pii()				=0; //[?]PII
		virtual void		pii(PStr var)		=0;
		virtual PStr		client_ip()			=0; //[?]사용자 IP주소
		virtual void		client_ip(PStr var)	=0;
	};

	class IResponseAuthenticationKey : public IResponseParent
	{
	public:
		IResponseAuthenticationKey()			{}
		virtual ~IResponseAuthenticationKey()	{}

		virtual PStr	authentication_key()			=0; //[?]인증키 값
		virtual void	authentication_key(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 6: Validate Authentication Key : 인증키 유효성 검사
	class IRequestValidateAuthenticationKey : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKey()				{}
		virtual ~IRequestValidateAuthenticationKey()	{}

		virtual INT32	user_no()						=0; //[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	authentication_key()			=0; //[?]인증키 값
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKey : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKey()			{}
		virtual ~IResponseValidateAuthenticationKey()	{}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 7: Validate Authentication Key with Extension : 인증키 유효성 검사
	class IRequestValidateAuthenticationKeyWithExtension : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKeyWithExtension()			{}
		virtual ~IRequestValidateAuthenticationKeyWithExtension()	{}

		virtual INT32	account_no()					=0; //[4]사용자 번호(복수개의 계정 존재시 Account No)
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	authentication_key()			=0; //[?]인증키 값
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKeyWithExtension : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKeyWithExtension()			{}
		virtual ~IResponseValidateAuthenticationKeyWithExtension()	{}

		virtual INT32	user_no()						=0; //[4]통합계정 User No
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]통합계정 User ID
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0; //[4]로그인한 Account NO
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]로그인한 Account ID
		virtual void	account_id(PStr var)			=0;
		virtual BYTE	channel_info()					=0;	//[1]채널링 정보
		virtual void	channel_info(BYTE var)			=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 8: Validate Authentication Key for Publisher : 인증키 유효성 검사
	class IRequestValidateAuthenticationKeyForPublisher : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKeyForPublisher()				{}
		virtual ~IRequestValidateAuthenticationKeyForPublisher()	{}

		virtual INT32	account_no()					=0; //[4]Publisher User No - 없을경우 0
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0;	//[?]Publisher User ID - 없을경우 ""
		virtual void	account_id(PStr var)			=0;
		virtual PStr	authentication_key()			=0; //[?]인증키 값
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKeyForPublisher : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKeyForPublisher()			{}
		virtual ~IResponseValidateAuthenticationKeyForPublisher()	{}

		virtual PStr	publisher_code()				=0;	//[?]Publisher의 처리 리턴 값 전달
		virtual void	publisher_code(PStr var)		=0;
		virtual INT32	user_no()						=0;	//[4]통합계정(GP 계정) User No
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0;	//[?]통합계정(GP 계정) User ID
		virtual void	user_id(PStr var)				=0;
		virtual INT32	publisher_no()					=0; //[4]로그인한 Publisher No - 없을경우 0
		virtual void	publisher_no(INT32 var)			=0;
		virtual PStr	publisher_id()					=0;	//[?]로그인한 Publisher ID - 없을경우 ""
		virtual void	publisher_id(PStr var)			=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 9: Validate Authentication Key with Parent Safe : 부모 안심 서비스 인증키 유효성 검사
	class IRequestValidateAuthenticationKeyWithParentSafe : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKeyWithParentSafe()			{}
		virtual ~IRequestValidateAuthenticationKeyWithParentSafe()	{}

		virtual INT32	account_no()					=0;	//[4]계정번호
		virtual void	account_no(INT32 var)			=0;
		virtual BYTE	channel_info()					=0;	//[1]채널링 정보
		virtual void	channel_info(BYTE var)			=0;
		virtual PStr	authentication_key()			=0; //[?]인증키 값
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKeyWithParentSafe : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKeyWithParentSafe()			{}
		virtual ~IResponseValidateAuthenticationKeyWithParentSafe()	{}

		virtual INT32	user_no()						=0; //[4]국내: 유저번호(주민등록번호 기준), ONE: request 계정번호 기준(ONE 계정 -> ONE 계정번호, legacy 계정 -> legacy 계정번호)
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]국내: 사용되지 않음, ONE: request 계정번호 기준(ONE 계정 -> ONE 계정 명, legacy 계정 -> legacy 계정 명)
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0; //[4]국내: 계정번호, ONE: 사용되지 않음
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]국내: 계정명, ONE: 사용되지 않음
		virtual void	account_id(PStr var)			=0;
		virtual BYTE	channel_info()					=0; //[1]채널링 정보
		virtual void	channel_info(BYTE var)			=0;
		virtual SHORT	age()							=0; //[2]유저 연령
		virtual void	age(SHORT var)					=0;
		virtual INT32	remain_time()					=0; //[4]남은 시간(분)
		virtual void	remain_time(INT32 var)			=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 10: Validate Authentication Key for R2 : 국내 R2 용 인증키 유효성 검사
	class IRequestValidateAuthenticationKeyForR2 : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKeyForR2()			{}
		virtual ~IRequestValidateAuthenticationKeyForR2()	{}

		virtual INT32	account_no()					=0;	//[4]계정번호
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	authentication_key()			=0; //[?]인증키 값
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	client_ip()						=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKeyForR2 : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKeyForR2()			{}
		virtual ~IResponseValidateAuthenticationKeyForR2()	{}

		virtual INT32	user_no()						=0; //[4]국내: 유저번호(주민등록번호 기준), ONE: request 계정번호 기준(ONE 계정 -> ONE 계정번호, legacy 계정 -> legacy 계정번호)
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]국내: 사용되지 않음, ONE: request 계정번호 기준(ONE 계정 -> ONE 계정 명, legacy 계정 -> legacy 계정 명)
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0; //[4]국내: 계정번호, ONE: 사용되지 않음
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]국내: 계정명, ONE: 사용되지 않음
		virtual void	account_id(PStr var)			=0;
		virtual BYTE	account_type()					=0; //[1]국내: R2 계정 타입
		virtual void	account_type(BYTE var)			=0;
		virtual BYTE	block_state()					=0; //[1]국내: 블록 국가 정보
		virtual void	block_state(BYTE var)			=0;
		virtual INT32	pcbang_index()					=0; //[4]국내: PC방 인덱스
		virtual void	pcbang_index(INT32 var)			=0;
		virtual PStr	phone_auth()					=0; //[?]국내: 폰 인증 키
		virtual void	phone_auth(PStr var)			=0;
		virtual INT32	is_phone_auth()					=0; //[4]국내: 폰 인증 여부
		virtual void	is_phone_auth(INT32 var)		=0;
		virtual PStr	auth_ip()						=0; //[?]국내: IP
		virtual void	auth_ip(PStr var)				=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 11: Validate Authentication Key with User Info : 인증키 유효성 검사 (유저 정보 확인)
	class IRequestValidateAuthenticationKeyWithUserInfo : public IRequestParent
	{
	public:
		IRequestValidateAuthenticationKeyWithUserInfo()				{}
		virtual ~IRequestValidateAuthenticationKeyWithUserInfo()	{}

		virtual PStr	callback_attribute()			=0; //[?]게임으로 전달될 콜백 데이터
		virtual void	callback_attribute(PStr var)	=0;
		virtual INT32	account_no()					=0; //[4]계정 번호
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	authentication_key()			=0; //[?]인증키 값
		virtual void	authentication_key(PStr var)	=0;
		virtual PStr	extension()						=0; //[?]추가 확장 요소를 위한 필드
		virtual void	extension(PStr var)				=0;
		virtual PStr	client_ip()						=0; //[?]사용자 IP 주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseValidateAuthenticationKeyWithUserInfo : public IResponseParent
	{
	public:
		IResponseValidateAuthenticationKeyWithUserInfo()			{}
		virtual ~IResponseValidateAuthenticationKeyWithUserInfo()	{}

		virtual PStr	callback_attribute()			=0; //[?]게임으로 전달될 콜백 데이터
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	provider_code()					=0; //[?]프로바이더 코드
		virtual void	provider_code(PStr var)			=0;
		virtual INT32	user_no()						=0; //[4]국내: 유저번호(주민등록번호 기준), ONE: request 계정번호 기준(ONE 계정 -> ONE 계정번호, legacy 계정 -> legacy 계정번호)
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]국내: 사용되지 않음, ONE: request 계정번호 기준(ONE 계정 -> ONE 계정 명, legacy 계정 -> legacy 계정 명)
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0; //[4]국내: 계정번호, ONE: 사용되지 않음
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]국내: 계정명, ONE: 사용되지 않음
		virtual void	account_id(PStr var)			=0;
		virtual PStr	extension()						=0; //[?]추가 확장 요소를 위한 필드
		virtual void	extension(PStr var)				=0;
	};



	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 12: Account Login : 웹젠 로그인
	class IRequestAccountLogin : public IRequestParent
	{
	public:
		IRequestAccountLogin()			{}
		virtual ~IRequestAccountLogin()	{}

		virtual PStr	account_id()			=0; //[?]WEBZEN AccountId
		virtual void	account_id(PStr var)	=0;
		virtual PStr	password()				=0; //[?]WEBZEN Account Password
		virtual void	password(PStr var)		=0;
		virtual PStr	pii()					=0; //[?]PII : 웹->게임런처를 통해 전달받는 사용자 PC 고유값
		virtual void	pii(PStr var)			=0;
		virtual PStr	client_ip()				=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)		=0;
	};

	class IResponseAccountLogin : public IResponseParent
	{
	public:
		IResponseAccountLogin()				{}
		virtual ~IResponseAccountLogin()	{}

		virtual INT32	user_no()							=0; //[4]사용자 번호
		virtual void	user_no(INT32 var)					=0;
		virtual BYTE	failure_count()						=0; //[1]10분간 로그인 실패횟수
		virtual void	failure_count(BYTE var)				=0;
		virtual PStr	user_type()							=0; //[?]유저구분 (fcs_constant.h "Table 7 Authorization User Type" 참조)
		virtual void	user_type(PStr var)					=0;
		virtual PStr	user_status()						=0; //[?]유저상태 (fcs_constant.h "Table 8 Authorization User Status" 참조)
		virtual void	user_status(PStr var)				=0;
		virtual PStr	security_provider_type()			=0; //[?]보안형태 (fcs_constant.h "Table 9 Authorization Security Provider Type" 참조)
		virtual void	security_provider_type(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 13: Account Logout : 웹젠 로그아웃
	class IRequestAccountLogout : public IRequestParent
	{
	public:
		IRequestAccountLogout()				{}
		virtual ~IRequestAccountLogout()	{}

		virtual INT32	user_no()			=0; //[4]사용자 번호
		virtual void	user_no(INT32 var)	=0;
		virtual PStr	client_ip()			=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)	=0;
	};

	class IResponseAccountLogout : public IResponseParent
	{
	public:
		IResponseAccountLogout()			{}
		virtual ~IResponseAccountLogout()	{}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 14: Set Account State : 계정의 마지막 로그인/로그아웃 서버 번호, IP, 시간, 누적로그인 횟수 업데이트
	class IRequestSetAccountState : public IRequestParent
	{
	public:
		IRequestSetAccountState()			{}
		virtual ~IRequestSetAccountState()	{}

		virtual INT32	account_no()				=0; //[4]계정 번호
		virtual void	account_no(INT32 var)		=0;
		virtual PStr	game_code()					=0;	//[?]게임 코드
		virtual void	game_code(PStr var)			=0;
		virtual INT32	server_id()					=0; //[4]서버 번호
		virtual void	server_id(INT32 var)		=0;
		virtual INT32	connect_state()				=0; //[4]0: 로그인, 1: 로그아웃
		virtual void	connect_state(INT32 var)	=0;
		virtual PStr	client_ip()					=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)			=0;
	};

	class IResponseSetAccountState : public IResponseParent
	{
	public:
		IResponseSetAccountState()			{}
		virtual ~IResponseSetAccountState()	{}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 15: Get PC Room GUID : IP로 ㅣPC방 고유번호 반환
	class IRequestGetPCRoomGuid : public IRequestParent
	{
	public:
		IRequestGetPCRoomGuid()				{}
		virtual ~IRequestGetPCRoomGuid()	{}

		virtual PStr	client_ip()			=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)	=0;
	};

	class IResponseGetPCRoomGuid : public IResponseParent
	{
	public:
		IResponseGetPCRoomGuid()			{}
		virtual ~IResponseGetPCRoomGuid()	{}

		virtual INT32	pc_room_guid()			=0;	//[4]PC방 고유번호
		virtual void	pc_room_guid(INT32 var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 16: Check Phone Auth User : 전화인증 가입계정 여부 확인
	class IRequestCheckPhoneAuthUser : public IRequestParent
	{
	public:
		IRequestCheckPhoneAuthUser()			{}
		virtual ~IRequestCheckPhoneAuthUser()	{}

		virtual INT32	account_no()			=0; //[4]계정 번호
		virtual void	account_no(INT32 var)	=0;
		virtual PStr	client_ip()				=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)		=0;
	};

	class IResponseCheckPhoneAuthUser : public IResponseParent
	{
	public:
		IResponseCheckPhoneAuthUser()			{}
		virtual ~IResponseCheckPhoneAuthUser()	{}

		virtual INT32	state()				=0;	//[4]0: 미가입, 1: 가입
		virtual void	state(INT32 var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 17: Get User Info : 계정 번호로 사용자 정보 확인
	class IRequestGetUserInfo : public IRequestParent
	{
	public:
		IRequestGetUserInfo()			{}
		virtual ~IRequestGetUserInfo()	{}

		virtual INT32	account_no()			=0; //[4]계정 번호
		virtual void	account_no(INT32 var)	=0;
		virtual PStr	client_ip()				=0; //[?]사용자 IP주소
		virtual void	client_ip(PStr var)		=0;
	};

	class IResponseGetUserInfo : public IResponseParent
	{
	public:
		IResponseGetUserInfo()			{}
		virtual ~IResponseGetUserInfo()	{}

		virtual INT32	user_no()				=0; //[4]유저 번호
		virtual void	user_no(INT32 var)		=0;
		virtual PStr	account_id()			=0; //[?]계정 명
		virtual void	account_id(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Authentication & Authorization Step 18: Get User Info With Extension : 계정번호로 사용자 정보 확인
	class IRequestGetUserInfoWithExtension : public IRequestParent
	{
	public:
		IRequestGetUserInfoWithExtension() {}
		virtual ~IRequestGetUserInfoWithExtension() {}

		virtual INT32	account_no() =0; //[4] 사용자 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	client_ip() =0; //[?] 사용자 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseGetUserInfoWithExtension : public IResponseParent
	{
	public:
		IResponseGetUserInfoWithExtension() {}
		virtual ~IResponseGetUserInfoWithExtension() {}

		virtual PStr	provider_code() =0; //[?] 프로바이더 코드
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
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
	// Basic Billing Step 1: Check Balance : 잔액조회
	class IRequestCheckBalance : public IRequestParent
	{
	public:
		IRequestCheckBalance()			{}
		virtual ~IRequestCheckBalance()	{}

		virtual INT32	user_no()			=0; //[4]사용자번호
		virtual void	user_no(INT32 var)	=0;
		virtual PStr	client_ip()			=0; //[?]사용자 IP 주소
		virtual void	client_ip(PStr var)	=0;
	};

	class IResponseCheckBalance : public IResponseParent
	{
	public:
		IResponseCheckBalance()				{}
		virtual ~IResponseCheckBalance()	{}

		virtual INT32	p_coin()				=0; // P Coin 잔액
		virtual void	p_coin(INT32 var)		=0;
		virtual INT32	c_coin()				=0; // C Coin 잔액
		virtual void	c_coin(INT32 var)		=0;
		virtual INT32	p_event_coin()			=0; // P Event Coin 잔액
		virtual void	p_event_coin(INT32 var)	=0;
		virtual INT32	c_event_coin()			=0; // C Event Coin 잔액
		virtual void	c_event_coin(INT32 var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 2: Item Purchase : 아이템 구매
	class IRequestItemPurchase : public IRequestParent
	{
	public:
		IRequestItemPurchase()			{}
		virtual ~IRequestItemPurchase()	{}

		virtual INT32						user_no()						=0; //[4]사용자 번호
		virtual void						user_no(INT32 var)				=0;
		virtual IArrayPtr<IRequestItem*>*	request_item()					=0; //[?]게임에서 구매하려는 아이템 정보의 구조체 배열
		virtual INT32						total_item_amount()				=0; //[4]구매하려는 아이템 금액의 합
		virtual void						total_item_amount(INT32 var)	=0;
		virtual PStr						item_order_id()					=0; //[?]게임에서 생성하는 주문번호(World No별 유니크 보장 필요)
		virtual void						item_order_id(PStr var)			=0;
		virtual INT32						character_no()					=0; //[4]캐릭터 번호
		virtual void						character_no(INT32 var)			=0;
		virtual PStr						character_name()				=0; //[?]캐릭터 이름
		virtual void						character_name(PStr var)		=0;
		virtual INT32						game_level()					=0;	//[4]게임레벨
		virtual void						game_level(INT32 var)			=0;
		virtual PStr						description()					=0; //[?]설명
		virtual void						description(PStr var)			=0;
		virtual PStr						client_ip()						=0; //[?]클라이언트 ip주소
		virtual void						client_ip(PStr var)				=0;
		virtual INT32						optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨
		virtual void						optional_world_no(INT32 var)	=0;
	};
	
	class IResponseItemPurchase : public IResponseParent
	{
	public:
		IResponseItemPurchase()				{}
		virtual ~IResponseItemPurchase()	{}

		virtual PStr				item_order_id()							=0; // 게임에서 전달한 유니크 주문번호
		virtual void				item_order_id(PStr var)					=0;
		virtual IArrayPtr<IResponseApprovalItem*>*	response_item_array()	=0;	// 아이템 승인정보 구조체 배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 3: Item Gift : 상품 선물
	class IRequestItemGift : public IRequestParent
	{
	public:
		IRequestItemGift()			{}
		virtual ~IRequestItemGift()	{}

		virtual INT32						user_no()							=0; //[4]사용자 번호
		virtual void						user_no(INT32 var)					=0;
		virtual IArrayPtr<IRequestItem*>*	request_item()						=0; //[?]게임에서 구매하려는 아이템 정보의 구조체 배열
		virtual INT32						total_item_amount()					=0; //[4]구매하려는 아이템 금액의 합
		virtual void						total_item_amount(INT32 var)		=0;
		virtual PStr						item_order_id()						=0; //[?]게임에서 생성하는 주문번호(World No별 유니크 보장 필요)
		virtual void						item_order_id(PStr var)				=0;
		virtual INT32						character_no()						=0; //[4]캐릭터 번호
		virtual void						character_no(INT32 var)				=0;
		virtual PStr						character_name()					=0; //[?]캐릭터 이름
		virtual void						character_name(PStr var)			=0;
		virtual INT32						game_level()						=0; //[4]게임레벨
		virtual void						game_level(INT32 var)				=0;
		virtual INT32						receive_world_no()					=0; //[4]선물 받는 캐릭터 월드 번호
		virtual void						receive_world_no(INT32 var)			=0;
		virtual INT32						receive_character_no()				=0; //[4]선물 받는 캐릭터 번호
		virtual void						receive_character_no(INT32 var)		=0;
		virtual PStr						receive_character_name()			=0; //[?]선물 받는 캐릭터 이름
		virtual void						receive_character_name(PStr var)	=0;
		virtual PStr						message()							=0; //[?]선물 메시지
		virtual void						message(PStr var)					=0;
		virtual PStr						description()						=0; //[?]설명
		virtual void						description(PStr var)				=0;
		virtual PStr						client_ip()							=0; //[?]클라이언트 ip주소
		virtual void						client_ip(PStr var)					=0;
		virtual INT32						optional_world_no()					=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨
		virtual void						optional_world_no(INT32 var)		=0;
	};

	class IResponseItemGift : public IResponseParent
	{
	public:
		IResponseItemGift()				{}
		virtual ~IResponseItemGift()	{}

		virtual PStr								item_order_id()				=0; // 게임에서 전달한 유니크 주문번호
		virtual void								item_order_id(PStr var)		=0;
		virtual IArrayPtr<IResponseApprovalItem*>*	response_item_array()		=0; // 아이템 승인정보 구조체 배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 4: Check Purchase : 구매 확인
	class IRequestCheckPurchase : public IRequestParent
	{
	public:
		IRequestCheckPurchase()				{}
		virtual ~IRequestCheckPurchase()	{}

		virtual PStr	item_order_id()			=0; //[?]구매/선물 시 사용한 주문번호
		virtual void	item_order_id(PStr var)	=0;
		virtual PStr	client_ip()				=0; //[?]클라이언트 IP주소
		virtual void	client_ip(PStr var)		=0;
	};

	class IResponseCheckPurchase : public IResponseParent
	{
	public:
		IResponseCheckPurchase()			{}
		virtual ~IResponseCheckPurchase()	{}

		virtual PStr	item_order_id()								=0; //[?]게임에서 전달한 유니크 주문번호
		virtual void	item_order_id(PStr var)						=0;
		virtual IArrayPtr<IPurchaseItem*>*	response_item_array()	=0; //[?]아이템 승인정보 구조체 배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 5: Cancel Purchase : 구매 취소
	class IRequestCancelPurchase : public IRequestParent
	{
	public:
		IRequestCancelPurchase()			{}
		virtual ~IRequestCancelPurchase()	{}

		virtual PStr	item_order_id()				=0; //[?]구매/선물 시 사용한 주문번호
		virtual void	item_order_id(PStr var)		=0;
		virtual INT32	purchase_no()				=0; //[4]구매승인 번호
		virtual void	purchase_no(INT32 var)		=0;
		virtual PStr	description()				=0; //[?]설명
		virtual void	description(PStr var)		=0;
		virtual PStr	client_ip()					=0; //[?]클라이언트 IP주소
		virtual void	client_ip(PStr var)			=0;
	};

	class IResponseCancelPurchase : public IResponseParent
	{
	public:
		IResponseCancelPurchase()			{}
		virtual ~IResponseCancelPurchase()	{}

		virtual PStr		item_order_id()			=0; //[?]게임에서 전달한 유니크 주문번호
		virtual void		item_order_id(PStr var)	=0;
		virtual INT32		purchase_no()			=0; //[4]주문번호
		virtual void		purchase_no(INT32 var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 6: Cancel Purchase by Order Id : 주문번호를 이용해서 전체 구매 취소
	class IRequestCancelPurchaseByOrderId : public IRequestParent
	{
	public:
		IRequestCancelPurchaseByOrderId()			{}
		virtual ~IRequestCancelPurchaseByOrderId()	{}

		virtual PStr	item_order_id()			=0; //[?]게임에서 전달한 유니크 주문번호
		virtual void	item_order_id(PStr var)	=0;
		virtual PStr	description()			=0; //[?]설명
		virtual void	description(PStr var)	=0;
		virtual PStr	client_ip()				=0; //[?]클라이언트 IP주소
		virtual void	client_ip(PStr var)		=0;
	};

	class IResponseCancelPurchaseByOrderId : public IResponseParent
	{
	public:
		IResponseCancelPurchaseByOrderId()			{}
		virtual ~IResponseCancelPurchaseByOrderId()	{}

		virtual PStr item_order_id()			=0; // 게임에서 전달한 유니크 주문번호
		virtual void item_order_id(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 7: Confirm Purchase by Order Id : 주문번호를 이용해서 전체 구매 승인
	//
	// 약 3분 동안 Confirm 하지 않으면 자동 취소 (3분은 FCS 서버 설정 사항)
	// 명시적으로 Confirm 혹은 Cancel 호출 권고. (자동 취소는 에러 사항으로 기록됨)
	class IRequestConfirmPurchaseByOrderId : public IRequestParent
	{
	public:
		IRequestConfirmPurchaseByOrderId()			{}
		virtual ~IRequestConfirmPurchaseByOrderId()	{}

		virtual PStr	item_order_id()					=0; //[?]주문/선물 시 사용했던 주문번호
		virtual void	item_order_id(PStr var)			=0;
		virtual PStr	description()					=0; //[?]설명
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]클라이언트 IP주소
		virtual void	client_ip(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨
		virtual void	optional_world_no(INT32 var)	=0;
	};

	class IResponseConfirmPurchaseByOrderId : public IResponseParent
	{
	public:
		IResponseConfirmPurchaseByOrderId()				{}
		virtual ~IResponseConfirmPurchaseByOrderId()	{}

		virtual PStr	item_order_id()				=0; // 게임에서 전달한 유니크 주문번호
		virtual void	item_order_id(PStr var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 8: Purchase List : 구매내역 조회
	class IRequestPurchaseList : public IRequestParent
	{
	public:
		IRequestPurchaseList()			{}
		virtual ~IRequestPurchaseList()	{}

		virtual INT32	user_no()					=0; //[4]사용자 번호
		virtual void	user_no(INT32 var)			=0;
		virtual INT64	begin_datetime()			=0; //[8]조회 시작일	: FILETIME : C#에선 DateTime.Ticks 값
		virtual void	begin_datetime(INT64 var)	=0;
		virtual INT64	end_datetime()				=0; //[8]조회 종료일	: FILETIME
		virtual void	end_datetime(INT64 var)		=0;
		virtual INT32	page_index()				=0; //[4]페이지 번호
		virtual void	page_index(INT32 var)		=0;
		virtual INT32	row_per_page()				=0; //[4]페이지당 데이터 개수
		virtual void	row_per_page(INT32 var)		=0;
		virtual PStr	client_ip()					=0; //[?]클라이언트 IP 주소
		virtual void	client_ip(PStr var)			=0;
	};

	class IResponsePurchaseList : public IResponseParent
	{
	public:
		IResponsePurchaseList()				{}
		virtual ~IResponsePurchaseList()	{}

		virtual INT32	total_row_count()									=0; //[4]전체 데이터 수
		virtual void	total_row_count(INT32 var)							=0;
		virtual IArrayPtr<IResponsePurchaseItem*>*	purchase_item_array()	=0;	//[?]구매 내역 구조체 배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Basic Billing Step 9: Exchange WCoin : WCoin을 게임 내에서 사용되는 포인트로 전환
	class IRequestExchangeWCoin : public IRequestParent
	{
	public:
		IRequestExchangeWCoin()				{}
		virtual ~IRequestExchangeWCoin()	{}

		virtual INT32	user_no()							=0; //[4]사용자 번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	order_id()							=0; //[?]전환 주문 번호 (게임에서 생성하여 전달)
		virtual void	order_id(PStr var)					=0;
		virtual INT32	exchange_wcoin_amount()				=0; //[4]환전할 WCoin 금액
		virtual void	exchange_wcoin_amount(INT32 var)	=0;
		virtual PStr	description()						=0; //[?]설명
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0; //[?]클라이언트 IP 주소
		virtual void	client_ip(PStr var)					=0;
	};

	class IResponseExchangeWCoin : public IResponseParent
	{
	public:
		IResponseExchangeWCoin()			{}
		virtual ~IResponseExchangeWCoin()	{}

		virtual PStr	order_id()							=0; //[?]게임에서 전달한 전환 주문 번호
		virtual void	order_id(PStr var)					=0;
		virtual INT32	used_payed_amount()					=0;	//[4]차감된 WCoin 금액
		virtual void	used_payed_amount(INT32 val)		=0;
		virtual INT32	used_bonus_amount()					=0;	//[4]차감된 보너스 WCoin 금액
		virtual void	used_bonus_amount(INT32 val)		=0;
		virtual INT32	purchase_no()						=0; //[4]고유 구매 번호
		virtual void	purchase_no(INT32 var)				=0;
	};
//## Basic Billing : END
//#################################################################################################
//##
//#################################################################################################
//## WShop Billing : START
//##
	// WShop Billing Step 1 : WShop Check Balance : 잔액조회
	class IRequestWShopCheckBalance : public IRequestParent
	{
	public:
		IRequestWShopCheckBalance() {}
		virtual ~IRequestWShopCheckBalance() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] 프로바이더 코드 (Get User Info With Ext에서 받은 값을 그대로 전달)
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] 게임에서 관리하는 월드 키
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호 (알 수 없거나 또는 사용자 경우 0이하 값)
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] 캐릭터 아이디 (알 수 없을 경우 빈 문자열)
		virtual void	character_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 사용자 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopCheckBalance : public IResponseParent
	{
	public:
		IResponseWShopCheckBalance() {}
		virtual ~IResponseWShopCheckBalance() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual INT64	coin() =0; //[8] 유료 WCoin 잔액
		virtual void	coin(INT64 var) = 0;
		virtual IArrayPtr<IJewelBalanceItem*>* jewel_balance_item_array() =0; //[?] 2차 화폐 잔액 아이템 배열
	};
	// WShop Billing Step 2 : WShopPurchase : 샵 아이템 구매
	class IRequestWShopPurchase : public IRequestParent
	{
	public:
		IRequestWShopPurchase() {}
		virtual ~IRequestWShopPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] 프로바이더 코드
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] 게임에서 관리하는 월드 키
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] 캐릭터 아이디
		virtual void	character_id(PStr var) = 0;
		virtual INT32	game_level() =0; //[4] 게임 레벨 (사용안할 경우  -1) : optional
		virtual void	game_level(INT32 var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
		virtual IArrayPtr<IWShopRequestPurchaseItem*>* request_purchase_item_array() =0; //[?] 요청 구매 아이템 배열
	};
	class IResponseWShopPurchase : public IResponseParent
	{
	public:
		IResponseWShopPurchase() {}
		virtual ~IResponseWShopPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual IArrayPtr<IWShopResponseApproval*>* purchase_item_array() =0; //[?] 아이템 구조체 배열
		virtual IArrayPtr<IJewelBalanceItem*>* jewel_balance_item_array() =0; //[?]2차 화폐 잔액 배열 (쥬얼 충전 관련 아이템 수령 후 업데이트된 잔액을 반환한다.)
	};

	// WShop Billing Step 3 : WShopCheckPurchase : 샵 아이템 구매 확인
	class IRequestWShopCheckPurchase : public IRequestParent
	{
	public:
		IRequestWShopCheckPurchase() {}
		virtual ~IRequestWShopCheckPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
		virtual IArrayPtr<IWShopRequestOrderId*>* request_order_id_array() =0; //[?] 요청 구매 아이템 배열
	};
	class IResponseWShopCheckPurchase : public IResponseParent
	{
	public:
		IResponseWShopCheckPurchase() {}
		virtual ~IResponseWShopCheckPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual IArrayPtr<IWShopResponseOrderStatus*>* response_order_status_array() = 0; //[?] 주문 별 상태 배열
	};
	// WShop Billing Step 4 : WShopCancelPurchase : 샵 아이템 구매 취소
	class IRequestWShopCancelPurchase : public IRequestParent
	{
	public:
		IRequestWShopCancelPurchase() {}
		virtual ~IRequestWShopCancelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
		virtual IArrayPtr<IWShopRequestOrderId*>* request_cancel_purchase_item_array() =0; //[?] 구매 취소 아이템 배열
	};
	class IResponseWShopCancelPurchase : public IResponseParent
	{
	public:
		IResponseWShopCancelPurchase() {}
		virtual ~IResponseWShopCancelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
	};
	// WShop Billing Step 5 : WShopConfirmPurchase : 샵 아이템 구매 승인
		class IRequestWShopConfirmPurchase : public IRequestParent
	{
	public:
		IRequestWShopConfirmPurchase() {}
		virtual ~IRequestWShopConfirmPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
		virtual IArrayPtr<IWShopRequestOrderId*>* request_order_id_array() =0; //[?] 요청 구매 아이템 배열
	};
	class IResponseWShopConfirmPurchase : public IResponseParent
	{
	public:
		IResponseWShopConfirmPurchase() {}
		virtual ~IResponseWShopConfirmPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
	};
// WShop Billing Step 6 : WShopGift : 샵 아이템 선물
	class IRequestWShopGift : public IRequestParent
	{
	public:
		IRequestWShopGift() {}
		virtual ~IRequestWShopGift() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] 프로바이더 코드
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] 게임에서 관리하는 서버 키
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] 캐릭터 아이디
		virtual void	character_id(PStr var) = 0;
		virtual INT32	game_level() =0; //[4] 게임레벨 (사용안할 경우  -1) : optional
		virtual void	game_level(INT32 var) = 0;
		virtual INT32	item_sale_no() =0; //[4] 아이템 판매 번호
		virtual void	item_sale_no(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT32	purchase_price() =0; //[4] 구매 금액 (할인룰 있는경우는 할인 적용된 금액)
		virtual void	purchase_price(INT32 var) = 0;
		virtual SHORT	order_quantity() =0; //[2] 주문 수량
		virtual void	order_quantity(SHORT var) = 0;
		virtual PStr	attribute0() =0; //[?] 속성 (클라라의 Property0) : optional
		virtual void	attribute0(PStr var) = 0;
		virtual PStr	attribute1() =0; //[?] 속성 (클라라의 Property1) : optional
		virtual void	attribute1(PStr var) = 0;
		virtual PStr	attribute2() =0; //[?] 속성 (클라라의 Property2) : optional
		virtual void	attribute2(PStr var) = 0;
		virtual PStr	attribute3() =0; //[?] 속성 (클라라의 Property3) : optional
		virtual void	attribute3(PStr var) = 0;
		virtual PStr	attribute4() =0; //[?] 속성 (클라라의 Property4) : optional
		virtual void	attribute4(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual INT32	receive_user_account_no() =0; //[4] 선물 받을 사용자 / 계정 번호
		virtual void	receive_user_account_no(INT32 var) = 0;
		virtual PStr	receive_world_key() =0; //[?] 선물 받을 캐릭터 월드 키
		virtual void	receive_world_key(PStr var) = 0;
		virtual INT64	receive_character_no() =0; //[8] 선물 받을 캐릭터 번호
		virtual void	receive_character_no(INT64 var) = 0;
		virtual PStr	receive_character_id() =0; //[?] 선물 받을 캐릭터 아이디
		virtual void	receive_character_id(PStr var) = 0;
		virtual PStr	send_message() =0; //[?] 선물 메시지
		virtual void	send_message(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopGift : public IResponseParent
	{
	public:
		IResponseWShopGift() {}
		virtual ~IResponseWShopGift() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual INT32	item_sale_no() =0; //[4] 아이템 판매 번호
		virtual void	item_sale_no(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT64	purchase_no() =0; //[8] 구매 번호
		virtual void	purchase_no(INT64 var) = 0;
		virtual PStr	item_code() =0; //[?] 게임에서 인지 가능한 아이템 코드 값
		virtual void	item_code(PStr var) = 0;
		virtual INT32	item_minute() =0; //[4] 아이템 기간(분)
		virtual void	item_minute(INT32 var) = 0;
		virtual SHORT	order_quantity() =0; //[2] 주문 수량
		virtual void	order_quantity(SHORT var) = 0;
		virtual PStr	attribute0() =0; //[?] 속성 (클라라의 Property0) : optional
		virtual void	attribute0(PStr var) = 0;
		virtual PStr	attribute1() =0; //[?] 속성 (클라라의 Property1) : optional
		virtual void	attribute1(PStr var) = 0;
		virtual PStr	attribute2() =0; //[?] 속성 (클라라의 Property2) : optional
		virtual void	attribute2(PStr var) = 0;
		virtual PStr	attribute3() =0; //[?] 속성 (클라라의 Property3) : optional
		virtual void	attribute3(PStr var) = 0;
		virtual PStr	attribute4() =0; //[?] 속성 (클라라의 Property4) : optional
		virtual void	attribute4(PStr var) = 0;
	};
	// WShop Billing Step 7 : WShopCheckGift : 선물 건 확인
	class IRequestWShopCheckGift : public IRequestParent
	{
	public:
		IRequestWShopCheckGift() {}
		virtual ~IRequestWShopCheckGift() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopCheckGift : public IResponseParent
	{
	public:
		IResponseWShopCheckGift() {}
		virtual ~IResponseWShopCheckGift() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] 현재 주문 상태 (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};
	// WShop Billing Step 8 : WShopCancelGift : 선물 건 취소
	class IRequestWShopCancelGift : public IRequestParent
	{
	public:
		IRequestWShopCancelGift() {}
		virtual ~IRequestWShopCancelGift() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopCancelGift : public IResponseParent
	{
	public:
		IResponseWShopCancelGift() {}
		virtual ~IResponseWShopCancelGift() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
	};
	// WShop Billing Step 9 : WShopConfirmGift : 쥬얼 충전 건 승인
	class IRequestWShopConfirmGift : public IRequestParent
	{
	public:
		IRequestWShopConfirmGift() {}
		virtual ~IRequestWShopConfirmGift() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopConfirmGift : public IResponseParent
	{
	public:
		IResponseWShopConfirmGift() {}
		virtual ~IResponseWShopConfirmGift() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
	};
	// WShop Billing Step 10 : WShopGetVersion : 샵 버전 정보 조회
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

		virtual INT64	shop_version() =0; //[8] 현재 샵 버전
		virtual void	shop_version(INT64 var) = 0;
	};

//## WShop Billing : END
//#################################################################################################
//##
//#################################################################################################
//## WShop Inventory : START
//##
	// WShop Inventory Step 1 : WShop Inquiry New Arrival : 일자 기준으로 새로 들어온 인벤토리 아이템 조회
	class IRequestWShopInquiryNewArrival : public IRequestParent
	{
	public:
		IRequestWShopInquiryNewArrival() {}
		virtual ~IRequestWShopInquiryNewArrival() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] 프로바이더 코드
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] 게임에서 관리하는 서버 키
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] 캐릭터 아이디
		virtual void	character_id(PStr var) = 0;
		virtual INT64	standard_date_time() =0; //[8] 기준 시각
		virtual void	standard_date_time(INT64 var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopInquiryNewArrival : public IResponseParent
	{
	public:
		IResponseWShopInquiryNewArrival() {}
		virtual ~IResponseWShopInquiryNewArrival() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual INT32	new_arrival_count() =0; //[4] 새로 들어온 아이템 수
		virtual void	new_arrival_count(INT32 var) = 0;
	};
	// WShop Inventory Step 2 : WShop Inquiry Inventory : 인벤토리 조회
	class IRequestWShopInquiryInventory : public IRequestParent
	{
	public:
		IRequestWShopInquiryInventory() {}
		virtual ~IRequestWShopInquiryInventory() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] 프로바이더 코드
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] 게임에서 관리하는 서버 키
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] 캐릭터 아이디
		virtual void	character_id(PStr var) = 0;
		virtual BYTE	expand_flags() =0; //[1] Cash Inventory Item Expand Flags (Table 11 Inquiry Cash Inventory Expand Flags)
		virtual void	expand_flags(BYTE var) = 0;
		virtual INT32	page_index() =0; //[4] 페이지 번호
		virtual void	page_index(INT32 var) = 0;
		virtual INT32	row_per_page() =0; //[4] 페이지 당 보여줄 아이템 수
		virtual void	row_per_page(INT32 var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopInquiryInventory : public IResponseParent
	{
	public:
		IResponseWShopInquiryInventory() {}
		virtual ~IResponseWShopInquiryInventory() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual BYTE	expand_flags() =0; //[1] Cash Inventory Item Expand Flags (Table 11 Inquiry Cash Inventory Expand Flags)
		virtual void	expand_flags(BYTE var) = 0;
		virtual INT32	total_inventory_count() =0; //[4] 총 인벤토리 수
		virtual void	total_inventory_count(INT32 var) = 0;
		virtual INT32	current_inventory_count() =0; //[4] 응답된 인벤토리 수
		virtual void	current_inventory_count(INT32 var) = 0;
		virtual IArrayPtr<IWShopInventoryItem*>* purchase_item_array() =0; //[?] 구매 인벤토리 아이템 배열
		virtual IArrayPtr<IWShopInventoryItem*>* package_item_array() =0; //[?] 묶음 인벤토리 아이템 배열
		virtual IArrayPtr<IWShopInventoryItem*>* lottery_item_array() =0; //[?] 복권 인벤토리 아이템 배열
		virtual IArrayPtr<IWShopInventoryItem*>* bonus_item_array() =0; //[?] 보너스 인벤토리 아이템 배열
	};
	// WShop Inventory Step 3 : WShop Pick Up : 인벤토리 수령
	class IRequestWShopPickUp : public IRequestParent
	{
	public:
		IRequestWShopPickUp() {}
		virtual ~IRequestWShopPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] 프로바이더 코드
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] 게임에서 관리하는 서버 키
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] 캐릭터 아이디
		virtual void	character_id(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual INT64	purchase_no() =0; //[8] 아이템 구매 번호
		virtual void	purchase_no(INT64 var) = 0;
		virtual SHORT	order_quantity() =0; //[2] 수령 아이템 수
		virtual void	order_quantity(SHORT var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 아이피
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopPickUp : public IResponseParent
	{
	public:
		IResponseWShopPickUp() {}
		virtual ~IResponseWShopPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual IArrayPtr<IWShopPickUpItem*>* pick_up_item_array() =0; //[?] 수령 아이템 배열
		virtual IArrayPtr<IJewelBalanceItem*>* jewel_balance_item_array() =0; //[?]2차 화폐 잔액 배열 (쥬얼 충전 관련 아이템 수령 후 업데이트된 잔액을 반환한다.)
	};
	// WShop Inventory Step 4 : WShop Check Pick Up : 인벤토리 수령 건 확인
	class IRequestWShopCheckPickUp : public IRequestParent
	{
	public:
		IRequestWShopCheckPickUp() {}
		virtual ~IRequestWShopCheckPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopCheckPickUp : public IResponseParent
	{
	public:
		IResponseWShopCheckPickUp() {}
		virtual ~IResponseWShopCheckPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] 현재 주문 상태 (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};
	// WShop Inventory Step 5 : WShop Cancel Pick Up : 인벤토리수령건취소
	class IRequestWShopCancelPickUp : public IRequestParent
	{
	public:
		IRequestWShopCancelPickUp() {}
		virtual ~IRequestWShopCancelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요)(100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopCancelPickUp : public IResponseParent
	{
	public:
		IResponseWShopCancelPickUp() {}
		virtual ~IResponseWShopCancelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
	};
	// WShop Inventory Step 6 : WShop Confirm Pick Up : 인벤토리수령건승인
	class IRequestWShopConfirmPickUp : public IRequestParent
	{
	public:
		IRequestWShopConfirmPickUp() {}
		virtual ~IRequestWShopConfirmPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문/선물 시 사용했던 주문번호
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseWShopConfirmPickUp : public IResponseParent
	{
	public:
		IResponseWShopConfirmPickUp() {}
		virtual ~IResponseWShopConfirmPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 전달한 주문번호
		virtual void	order_id(PStr var) = 0;
	};

//## WShop Inventory : END
//#################################################################################################
//##
//#################################################################################################
//## Jewel Billing : START
//##
	// Jewel Step 1  : Charge Jewel : 쥬얼충전요청
	class IRequestChargeJewel : public IRequestParent
	{
	public:
		IRequestChargeJewel() {}
		virtual ~IRequestChargeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] 프로바이더 코드
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] 게임에서 관리하는 서버 키
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] 캐릭터 아이디
		virtual void	character_id(PStr var) = 0;
		virtual INT32	game_level() =0; //[4] 게임레벨 (사용안할 경우  -1) : optional
		virtual void	game_level(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	payment_type() =0; //[?] 충전 유형 (Table 19 Payment Type)
		virtual void	payment_type(PStr var) = 0;
		virtual INT32	cash_type() =0; //[?] 캐시 타입 (Table 18 Cash Type)
		virtual void	cash_type(INT32 var) = 0;
		virtual PStr	item_code() = 0; //[?] 아이템 코드
		virtual void	item_code(PStr var) = 0;
		virtual PStr	payment_product_name() =0; //[?] 충전 상품 명
		virtual void	payment_product_name(PStr var) = 0;
		virtual INT32	charge_amount() =0; //[4] 충전 금액
		virtual void	charge_amount(INT32 var) = 0;
		virtual INT32	bonus_amount() =0; //[4] 보너스 충전 금액
		virtual void	bonus_amount(INT32 var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseChargeJewel : public IResponseParent
	{
	public:
		IResponseChargeJewel() {}
		virtual ~IResponseChargeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 2  : Check Jewel Charge : 쥬얼충전건확인
	class IRequestCheckJewelCharge : public IRequestParent
	{
	public:
		IRequestCheckJewelCharge() {}
		virtual ~IRequestCheckJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCheckJewelCharge : public IResponseParent
	{
	public:
		IResponseCheckJewelCharge() {}
		virtual ~IResponseCheckJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] 현재 주문 상태 (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};
	// Jewel Step 3  : Cancel Jewel Charge : 쥬얼충전건취소
	class IRequestCancelJewelCharge : public IRequestParent
	{
	public:
		IRequestCancelJewelCharge() {}
		virtual ~IRequestCancelJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요)(100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCancelJewelCharge : public IResponseParent
	{
	public:
		IResponseCancelJewelCharge() {}
		virtual ~IResponseCancelJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 4  : Confirm Jewel Charge : 쥬얼충전건승인
	class IRequestConfirmJewelCharge : public IRequestParent
	{
	public:
		IRequestConfirmJewelCharge() {}
		virtual ~IRequestConfirmJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseConfirmJewelCharge : public IResponseParent
	{
	public:
		IResponseConfirmJewelCharge() {}
		virtual ~IResponseConfirmJewelCharge() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 5  : Purchase Jewel Item : 쥬얼소진
	class IRequestPurchaseJewelItem : public IRequestParent
	{
	public:
		IRequestPurchaseJewelItem() {}
		virtual ~IRequestPurchaseJewelItem() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	provider_code() =0; //[?] 프로바이더 코드
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] 게임에서 관리하는 서버 키
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] 캐릭터 아이디
		virtual void	character_id(PStr var) = 0;
		virtual INT32	game_level() =0; //[4] 게임레벨 (사용안할 경우  -1) : optional
		virtual void	game_level(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	item_code() =0; //[?] 게임에서 알고 있는 아이템 식별자
		virtual void	item_code(PStr var) = 0;
		virtual PStr	item_name() =0; //[?] 게임에서 알고 있는 아이템 명
		virtual void	item_name(PStr var) = 0;
		virtual INT32	cash_type() =0; //[?] 소진 캐시 유형 (Table 18 Cash Type)
		virtual void	cash_type(INT32 var) = 0;
		virtual INT32	purchase_cost() =0; //[4] 아이템 원가
		virtual void	purchase_cost(INT32 var) = 0;
		virtual INT32	purchase_quantity() =0; //[4] 아이템 수량
		virtual void	purchase_quantity(INT32 var) = 0;
		virtual INT32	purchase_amount() =0; //[4] 구매하려는 아이템의 총 금액
		virtual void	purchase_amount(INT32 var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponsePurchaseJewelItem : public IResponseParent
	{
	public:
		IResponsePurchaseJewelItem() {}
		virtual ~IResponsePurchaseJewelItem() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 6  : Check Purchase Jewel : 쥬얼소진건확인
	class IRequestCheckPurchaseJewel : public IRequestParent
	{
	public:
		IRequestCheckPurchaseJewel() {}
		virtual ~IRequestCheckPurchaseJewel() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCheckPurchaseJewel : public IResponseParent
	{
	public:
		IResponseCheckPurchaseJewel() {}
		virtual ~IResponseCheckPurchaseJewel() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 7  : Cancel Jewel Purchase : 쥬얼소진건취소
	class IRequestCancelJewelPurchase : public IRequestParent
	{
	public:
		IRequestCancelJewelPurchase() {}
		virtual ~IRequestCancelJewelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문/선물 시 사용했던 주문번호
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCancelJewelPurchase : public IResponseParent
	{
	public:
		IResponseCancelJewelPurchase() {}
		virtual ~IResponseCancelJewelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 전달한 주문번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 8  : Confirm Jewel Purchase : 쥬얼소진건승인
	class IRequestConfirmJewelPurchase : public IRequestParent
	{
	public:
		IRequestConfirmJewelPurchase() {}
		virtual ~IRequestConfirmJewelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문/선물 시 사용했던 주문번호
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseConfirmJewelPurchase : public IResponseParent
	{
	public:
		IResponseConfirmJewelPurchase() {}
		virtual ~IResponseConfirmJewelPurchase() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 전달한 주문번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 9  : Trade Jewel : 쥬얼경매장거래
	class IRequestTradeJewel : public IRequestParent
	{
	public:
		IRequestTradeJewel() {}
		virtual ~IRequestTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] 게임 서버로 전달되는 속성 : optional
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	provider_code() =0; //[?] 프로바이더 코드
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] 게임에서 관리하는 서버 키
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] 캐릭터 아이디
		virtual void	character_id(PStr var) = 0;
		virtual INT32	game_level() =0; //[4] 게임레벨 (사용안할 경우  -1) : optional
		virtual void	game_level(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	item_code() =0; //[?] 게임에서 알고 있는 아이템 식별자
		virtual void	item_code(PStr var) = 0;
		virtual PStr	item_name() =0; //[?] 게임에서 알고 있는 아이템 명
		virtual void	item_name(PStr var) = 0;
		virtual INT32	purchase_cost() =0; //[4] 아이템 원가
		virtual void	purchase_cost(INT32 var) = 0;
		virtual INT32	purchase_quantity() =0; //[4] 구매 수량
		virtual void	purchase_quantity(INT32 var) = 0;
		virtual INT32	purchase_amount() =0; //[4] 구매하려는 아이템의 총 금액
		virtual void	purchase_amount(INT32 var) = 0;
		virtual INT32	target_account_no() =0; //[4] 거래 대상(아이템을 등록한) 사용자 번호     [국내] 계정 번호     [글로벌] 사용자 번호
		virtual void	target_account_no(INT32 var) = 0;
		virtual INT64	target_character_no() =0; //[8] 거래 대상 캐릭터 번호
		virtual void	target_character_no(INT64 var) = 0;
		virtual PStr	target_character_id() =0; //[?] 거래 대상 캐릭터 아이디
		virtual void	target_character_id(PStr var) = 0;
		virtual INT32	target_user_grade() =0; //[4] 거래 대상(경매장 아이템 등록 시점)의 사용자 등급 (Table 24 User Grade)
		virtual void	target_user_grade(INT32 var) = 0;
		virtual PStr	send_message() =0; //[?] 거래 메시지
		virtual void	send_message(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseTradeJewel : public IResponseParent
	{
	public:
		IResponseTradeJewel() {}
		virtual ~IResponseTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 10 : Check Trade Jewel : 쥬얼경매장거래건확인 
	class IRequestCheckTradeJewel : public IRequestParent
	{
	public:
		IRequestCheckTradeJewel() {}
		virtual ~IRequestCheckTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCheckTradeJewel : public IResponseParent
	{
	public:
		IResponseCheckTradeJewel() {}
		virtual ~IResponseCheckTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] 현재 주문 상태 (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};
	// Jewel Step 11 : Cancel Jewel Trade : 쥬얼경매장거래건취소
	class IRequestCancelJewelTrade : public IRequestParent
	{
	public:
		IRequestCancelJewelTrade() {}
		virtual ~IRequestCancelJewelTrade() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문/선물 시 사용했던 주문번호
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCancelJewelTrade : public IResponseParent
	{
	public:
		IResponseCancelJewelTrade() {}
		virtual ~IResponseCancelJewelTrade() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 전달한 주문번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 12 : Confirm Jewel Trade : 쥬얼 경매장 거래건 승인
	class IRequestConfirmJewelTrade : public IRequestParent
	{
	public:
		IRequestConfirmJewelTrade() {}
		virtual ~IRequestConfirmJewelTrade() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 주문/선물 시 사용했던 주문번호
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseConfirmJewelTrade : public IResponseParent
	{
	public:
		IResponseConfirmJewelTrade() {}
		virtual ~IResponseConfirmJewelTrade() {}

		virtual PStr	callback_attribute() =0; //[?] 게임서버에 전달되는 속성 값 : optional
		virtual void	callback_attribute(PStr var)=0;
		virtual PStr	order_id() =0; //[?] 게임에서 전달한 주문번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 13 : Pick Up Trade Jewel : 쥬얼 경매장 판매금액 수령(판매자)
	class IRequestPickUpTradeJewel : public IRequestParent
	{
	public:
		IRequestPickUpTradeJewel() {}
		virtual ~IRequestPickUpTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] 게임 서버로 전달되는 속성 : optional
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	provider_code() =0; //[?] 프로바이더 코드 (Get User Info With Ext에서 받은 값을 그대로 전달)
		virtual void	provider_code(PStr var) = 0;
		virtual INT32	user_no() =0; //[4] 사용자 번호
		virtual void	user_no(INT32 var) = 0;
		virtual PStr	user_id() =0; //[?] 사용자 아이디
		virtual void	user_id(PStr var) = 0;
		virtual INT32	account_no() =0; //[4] 계정 번호
		virtual void	account_no(INT32 var) = 0;
		virtual PStr	account_id() =0; //[?] 계정 아이디
		virtual void	account_id(PStr var) = 0;
		virtual PStr	world_key() =0; //[?] 게임에서 관리하는 월드 키
		virtual void	world_key(PStr var) = 0;
		virtual INT64	character_no() =0; //[8] 캐릭터 번호 (알 수 없거나 또는 사용자 경우 0이하 값)
		virtual void	character_no(INT64 var) = 0;
		virtual PStr	character_id() =0; //[?] 캐릭터 아이디 (알 수 없을 경우 빈 문자열)
		virtual void	character_id(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	trade_order_id() =0; //[?] 이 아이템을 구매자가 경매장에서 구매했을 때 생성했던 주문번호
		virtual void	trade_order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponsePickUpTradeJewel : public IResponseParent
	{
	public:
		IResponsePickUpTradeJewel() {}
		virtual ~IResponsePickUpTradeJewel() {}

		virtual PStr	callback_attribute() =0; //[?] 게임 서버로 전달되는 속성
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT32	commission_amount() =0; //[4] 판매 수수료
		virtual void	commission_amount(INT32 var) = 0;
		virtual INT32	receive_amount() =0; //[4] (수수료 차감 후) 최종적으로 판매자가 수령 받을 금액
		virtual void	receive_amount(INT32 var) = 0;
		virtual IArrayPtr<IJewelBalanceItem*>* jewel_balance_item_array() =0; //[?] 2차 화폐 잔액 배열(판매 금액 수령 후의 업데이트된 잔액을 반환한다.)
	};

	// Jewel Step 14 : Check Trade Jewel Pick Up : 경매장 판매금액 수령건 확인
	class IRequestCheckTradeJewelPickUp : public IRequestParent
	{
	public:
		IRequestCheckTradeJewelPickUp() {}
		virtual ~IRequestCheckTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임 서버로 전달되는 속성 : optional
		virtual void	callback_attribute(PStr var) = 0;
		virtual BYTE	return_structure_type() =0; //[1] 응답 구조체 형식 (Table 5 Return Structure Types)
		virtual void	return_structure_type(BYTE var) = 0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문번호 (World별 유니크 보장 필요) (100자까지 사용가능)
		virtual void	order_id(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCheckTradeJewelPickUp : public IResponseParent
	{
	public:
		IResponseCheckTradeJewelPickUp() {}
		virtual ~IResponseCheckTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임 서버로 전달되는 속성
		virtual void	callback_attribute(PStr var) = 0;
		virtual BYTE	return_structure_type() =0; //[1] 응답 구조체 형식 (Table 5 Return Structure Types)
		virtual void	return_structure_type(BYTE var) = 0;
		virtual PStr	order_id() =0; //[?] 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] 현재 주문 상태 (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};
	// Jewel Step 15 : Cancel Trade Jewel Pick Up : 경매장 판매금액 수령건 취소
	class IRequestCancelTradeJewelPickUp : public IRequestParent
	{
	public:
		IRequestCancelTradeJewelPickUp() {}
		virtual ~IRequestCancelTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임 서버로 전달되는 속성 : optional
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] 주문/선물 시 사용했던 주문번호
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseCancelTradeJewelPickUp : public IResponseParent
	{
	public:
		IResponseCancelTradeJewelPickUp() {}
		virtual ~IResponseCancelTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임 서버로 전달되는 속성
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] 게임에서 전달한 주문번호
		virtual void	order_id(PStr var) = 0;
	};
	// Jewel Step 16 : Confirm Trade Jewel Pick Up : 경매장 판매금액 수령건 승인
	class IRequestConfirmTradeJewelPickUp : public IRequestParent
	{
	public:
		IRequestConfirmTradeJewelPickUp() {}
		virtual ~IRequestConfirmTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임 서버로 전달되는 속성 : optional
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] 주문/선물 시 사용했던 주문번호
		virtual void	order_id(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
		virtual PStr	client_ip() =0; //[?] 클라이언트 IP주소
		virtual void	client_ip(PStr var) = 0;
	};
	class IResponseConfirmTradeJewelPickUp : public IResponseParent
	{
	public:
		IResponseConfirmTradeJewelPickUp() {}
		virtual ~IResponseConfirmTradeJewelPickUp() {}

		virtual PStr	callback_attribute() =0; //[?] 게임 서버로 전달되는 속성
		virtual void	callback_attribute(PStr var) = 0;
		virtual PStr	order_id() =0; //[?] 게임에서 전달한 주문번호
		virtual void	order_id(PStr var) = 0;
	};

//## Jewel Billing : END
//#################################################################################################
//##
//#################################################################################################
//## Advanced Biling - Cash Inventory : START
//##
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 1: Inquiry Cash Inventory - 캐시인벤토리조회
	class IRequestInquiryCashInventory : public IRequestParent
	{
	public:
		IRequestInquiryCashInventory()			{}
		virtual ~IRequestInquiryCashInventory()	{}

		//get,set
		virtual BYTE	item_expand_flag()				=0; //[1]Cash Inventory Item Expand Flags (fcs_constant.h의 "Table 11 Inquiry Cash Inventory Expand Flags" 참조)
		virtual void	item_expand_flag(BYTE var)		=0;
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	page_index()					=0; //[4]페이지번호
		virtual void	page_index(INT32 var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터확인)
		virtual void	row_per_page(INT32 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
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
		virtual	INT32								total_row_count()			=0; //[4]인벤토리수량
		virtual void								total_row_count(INT32 var)	=0;
		virtual IArrayPtr<ICashInventoryItems*>*	items()						=0; //[?]아이템구조체배열
		virtual IArrayPtr<IPackageItem*>*			package_items()				=0; //[?] 데이터 혹은 item_expand_flag 없는 경우 없음
		virtual IArrayPtr<ILotteryItem*>*			lottery_items()				=0; //[?] 데이터 혹은 item_expand_flag 없는 경우 없음
		virtual IArrayPtr<IBonusItem*>*				bonus_items()				=0; //[?] 데이터 혹은 item_expand_flag 없는 경우 없음
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 2: Inquiry Cash Inventory by Bind Attribute - 아이템 귀속 형태에 따른 캐시인벤토리조회
	class IRequestInquiryCashInventoryByBindAttribute : public IRequestParent
	{
	public:
		IRequestInquiryCashInventoryByBindAttribute()			{}
		virtual ~IRequestInquiryCashInventoryByBindAttribute()	{}

		//get,set
		virtual BYTE	item_expand_flag()				=0; //[1]Cash Inventory Item Expand Flags (fcs_constant.h의 "Table 11 Inquiry Cash Inventory Expand Flags" 참조)
		virtual void	item_expand_flag(BYTE var)		=0;
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]계정 아이디(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	page_index()					=0; //[4]페이지번호
		virtual void	page_index(INT32 var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터확인)
		virtual void	row_per_page(INT32 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
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
		virtual	INT32											total_row_count()			=0; //[4]인벤토리수량
		virtual void											total_row_count(INT32 var)	=0;
		virtual IArrayPtr<ICashInventoryItemsByBindAttribute*>*	items()						=0; //[?]아이템구조체배열
		virtual IArrayPtr<IPackageItemByBindAttribute*>*		package_items()				=0; //[?] 데이터 혹은 item_expand_flag 없는 경우 없음
		virtual IArrayPtr<ILotteryItemByBindAttribute*>*		lottery_items()				=0; //[?] 데이터 혹은 item_expand_flag 없는 경우 없음
		virtual IArrayPtr<IBonusItemByBindAttribute*>*			bonus_items()				=0; //[?] 데이터 혹은 item_expand_flag 없는 경우 없음
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 3: Pickup Cash Inventory Item - 캐시인벤토리수령
	class IRequestPickupCashInventoryItem : public IRequestParent
	{
	public:
		IRequestPickupCashInventoryItem()			{}
		virtual ~IRequestPickupCashInventoryItem()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	optional_world_no()					=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템번호
		virtual void	item_no(INT32 var)					=0;
		virtual bool	is_reserved_character()				=0; //[1]현재전달된캐릭터정보를이용해서수령을제한하고싶을경우사용(사용자계정단위로구매를진행했을때만사용할수있다.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]받는타입. (fcs_constants.h - "ETC. Receive Type : 받는 타입" 참조)
		virtual void	receive_type(BYTE var)				=0;
		virtual SHORT	pickup_quantity()					=0; //[2]수령수량
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]설명
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponsePickupCashInventoryItem : public IResponseParent
	{
	public:
		IResponsePickupCashInventoryItem()			{}
		virtual ~IResponsePickupCashInventoryItem()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 4: Pickup Cash Inventory Item by Bind Attribute - 아이템 귀속 형태에 따른 캐시인벤토리수령
	class IRequestPickupCashInventoryItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestPickupCashInventoryItemByBindAttribute()			{}
		virtual ~IRequestPickupCashInventoryItemByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]계정 ID(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)				=0;
		virtual INT32	optional_world_no()					=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템번호
		virtual void	item_no(INT32 var)					=0;
		virtual bool	is_reserved_character()				=0; //[1]현재전달된캐릭터정보를이용해서수령을제한하고싶을경우사용(사용자계정단위로구매를진행했을때만사용할수있다.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]받는타입. (fcs_constants.h - "ETC. Receive Type : 받는 타입" 참조)
		virtual void	receive_type(BYTE var)				=0;
		virtual SHORT	pickup_quantity()					=0; //[2]수령수량
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]설명
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponsePickupCashInventoryItemByBindAttribute : public IResponseParent
	{
	public:
		IResponsePickupCashInventoryItemByBindAttribute()			{}
		virtual ~IResponsePickupCashInventoryItemByBindAttribute()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 5: Cancel Pickup Cash Inventory Item - 캐시인벤토리수령취소
	class IRequestCancelCashInventoryItem : public IRequestParent
	{
	public:
		IRequestCancelCashInventoryItem()			{}
		virtual ~IRequestCancelCashInventoryItem()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	optional_world_no()					=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템번호
		virtual void	item_no(INT32 var)					=0;
		virtual bool	is_reserved_character()				=0; //[1]현재전달된캐릭터정보를이용해서수령을제한하고싶을경우사용(사용자계정단위로구매를진행했을때만사용할수있다.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]받는타입. 요청수령:0x01, 자동수령:0x02, 강제수령:0x03, 만료강제수령:0x04, 삭제:0x05, 만료삭제:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual SHORT	pickup_quantity()					=0; //[2]수령수량
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]설명
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponseCancelCashInventoryItem : public IResponseParent
	{
	public:
		IResponseCancelCashInventoryItem()			{}
		virtual ~IResponseCancelCashInventoryItem()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 6: Cancel Pickup Cash Inventory Item by Bind Attribute - 아이템 귀속 형태에 따른 캐시인벤토리수령취소
	class IRequestCancelCashInventoryItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestCancelCashInventoryItemByBindAttribute()			{}
		virtual ~IRequestCancelCashInventoryItemByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]계정 ID(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)				=0;
		virtual INT32	optional_world_no()					=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템번호
		virtual void	item_no(INT32 var)					=0;
		virtual bool	is_reserved_character()				=0; //[1]현재전달된캐릭터정보를이용해서수령을제한하고싶을경우사용(사용자계정단위로구매를진행했을때만사용할수있다.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]받는타입. 요청수령:0x01, 자동수령:0x02, 강제수령:0x03, 만료강제수령:0x04, 삭제:0x05, 만료삭제:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual SHORT	pickup_quantity()					=0; //[2]수령수량
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]설명
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponseCancelCashInventoryItemByBindAttribute : public IResponseParent
	{
	public:
		IResponseCancelCashInventoryItemByBindAttribute()			{}
		virtual ~IResponseCancelCashInventoryItemByBindAttribute()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)		=0;
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 7: Pickup Cash Sub Inventory Item - 개별캐시인벤토리수령
	class IRequestPickupCashSubInventoryItem : public IRequestParent
	{
	public:
		IRequestPickupCashSubInventoryItem()			{}
		virtual ~IRequestPickupCashSubInventoryItem()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	optional_world_no()					=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0;	//[4]아이템번호
		virtual void	item_no(INT32 var)					=0;
		virtual INT64	inventory_no()						=0; //[8]인벤토리번호
		virtual void	inventory_no(INT64 var)				=0;
		virtual bool	is_reserved_character()				=0; //[1]현재전달된캐릭터정보를이용해서수령을제한하고싶을경우사용(사용자계정단위로구매를진행했을때만사용할수있다.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]받는타입. 요청수령:0x01, 자동수령:0x02, 강제수령:0x03, 만료강제수령:0x04, 삭제:0x05, 만료삭제:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual BYTE	inventory_type()					=0; //[1]인벤토리타입. Package Inventories:0x01, Lottery Inventories:0x02, Bonus Inventories:0x04
		virtual void	inventory_type(BYTE var)			=0;
		virtual SHORT	pickup_quantity()					=0; //[2]수령수량
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]설명
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponsePickupCashSubInventoryItem : public IResponseParent
	{
	public:
		IResponsePickupCashSubInventoryItem()			{}
		virtual ~IResponsePickupCashSubInventoryItem()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 8: Pickup Cash Sub Inventory Item by Bind Attribute - 아이템 귀속 형태에 따른 개별캐시인벤토리수령
	class IRequestPickupCashSubInventoryItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestPickupCashSubInventoryItemByBindAttribute()				{}
		virtual ~IRequestPickupCashSubInventoryItemByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]계정 ID(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)				=0;
		virtual INT32	optional_world_no()					=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0;	//[4]아이템번호
		virtual void	item_no(INT32 var)					=0;
		virtual INT64	inventory_no()						=0; //[8]인벤토리번호
		virtual void	inventory_no(INT64 var)				=0;
		virtual bool	is_reserved_character()				=0; //[1]현재전달된캐릭터정보를이용해서수령을제한하고싶을경우사용(사용자계정단위로구매를진행했을때만사용할수있다.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]받는타입. 요청수령:0x01, 자동수령:0x02, 강제수령:0x03, 만료강제수령:0x04, 삭제:0x05, 만료삭제:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual BYTE	inventory_type()					=0; //[1]인벤토리타입. Package Inventories:0x01, Lottery Inventories:0x02, Bonus Inventories:0x04
		virtual void	inventory_type(BYTE var)			=0;
		virtual SHORT	pickup_quantity()					=0; //[2]수령수량
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]설명
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponsePickupCashSubInventoryItemByBindAttribute : public IResponseParent
	{
	public:
		IResponsePickupCashSubInventoryItemByBindAttribute()			{}
		virtual ~IResponsePickupCashSubInventoryItemByBindAttribute()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 9: Cancel Cash Sub Inventory Item - 개별캐시인벤토리취소
	class IRequestCancelCashSubInventoryItem : public IRequestParent
	{
	public:
		IRequestCancelCashSubInventoryItem()			{}
		virtual ~IRequestCancelCashSubInventoryItem()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	optional_world_no()					=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템번호
		virtual void	item_no(INT32 var)					=0;
		virtual INT64	inventory_no()						=0; //[8]인벤토리번호
		virtual void	inventory_no(INT64 var)				=0;
		virtual bool	is_reserved_character()				=0; //[1]현재전달된캐릭터정보를이용해서수령을제한하고싶을경우사용(사용자계정단위로구매를진행했을때만사용할수있다.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]받는타입. 요청수령:0x01, 자동수령:0x02, 강제수령:0x03, 만료강제수령:0x04, 삭제:0x05, 만료삭제:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual BYTE	inventory_type()					=0; //[1]인벤토리타입. Package Inventories:0x01, LotteryInventories:0x02, Bonus Inventories:0x04
		virtual void	inventory_type(BYTE var)			=0;
		virtual SHORT	pickup_quantity()					=0; //[2]수령수량
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]설명
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponseCancelCashSubInventoryItem : public IResponseParent
	{
	public:
		IResponseCancelCashSubInventoryItem()			{}
		virtual ~IResponseCancelCashSubInventoryItem()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 10: Cancel Cash Sub Inventory Item by Bind Attribute - 아이템 귀속 형태에 따른 개별캐시인벤토리취소
	class IRequestCancelCashSubInventoryItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestCancelCashSubInventoryItemByBindAttribute()				{}
		virtual ~IRequestCancelCashSubInventoryItemByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()							=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]계정 ID(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)				=0;
		virtual INT32	optional_world_no()					=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)		=0;
		virtual PStr	world_key()							=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)				=0;
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템번호
		virtual void	item_no(INT32 var)					=0;
		virtual INT64	inventory_no()						=0; //[8]인벤토리번호
		virtual void	inventory_no(INT64 var)				=0;
		virtual bool	is_reserved_character()				=0; //[1]현재전달된캐릭터정보를이용해서수령을제한하고싶을경우사용(사용자계정단위로구매를진행했을때만사용할수있다.)
		virtual void	is_reserved_character(bool var)		=0;
		virtual BYTE	receive_type()						=0; //[1]받는타입. 요청수령:0x01, 자동수령:0x02, 강제수령:0x03, 만료강제수령:0x04, 삭제:0x05, 만료삭제:0x06
		virtual void	receive_type(BYTE var)				=0;
		virtual BYTE	inventory_type()					=0; //[1]인벤토리타입. Package Inventories:0x01, LotteryInventories:0x02, Bonus Inventories:0x04
		virtual void	inventory_type(BYTE var)			=0;
		virtual SHORT	pickup_quantity()					=0; //[2]수령수량
		virtual void	pickup_quantity(SHORT var)			=0;
		virtual PStr	callback_attribute()				=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)		=0;
		virtual PStr	description()						=0; //[?]설명
		virtual void	description(PStr var)				=0;
		virtual PStr	client_ip()							=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)					=0;
	};
	class IResponseCancelCashSubInventoryItemByBindAttribute : public IResponseParent
	{
	public:
		IResponseCancelCashSubInventoryItemByBindAttribute()			{}
		virtual ~IResponseCancelCashSubInventoryItemByBindAttribute()	{}

		//get,set
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual SHORT	remain_quantity()				=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)		=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 11: Inquiry Pickup Standby Cash Purchase No - 게임에서 수령 가능한 아이템 구매번호 리스트 조회
	class IRequestInquiryPickupStandbyCashPurchaseNo : public IRequestParent
	{
	public:
		IRequestInquiryPickupStandbyCashPurchaseNo()			{}
		virtual ~IRequestInquiryPickupStandbyCashPurchaseNo()	{}

		//get,set
		virtual INT32	optional_world_no()				=0; //[4]Initialize 수행한 World No와 다른 World No로 조회할 경우 사용한다. 사용자 계정 경우 -1 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]계정 ID(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseInquiryPickupStandbyCashPurchaseNo : public IResponseParent
	{
	public:
		IResponseInquiryPickupStandbyCashPurchaseNo()			{}
		virtual ~IResponseInquiryPickupStandbyCashPurchaseNo()	{}

		//get,set
		virtual PStr						callback_attribute()		=0; //[?]요청시전달한속성값
		virtual void						callback_attribute(PStr var)=0;
		virtual INT32						total_row_count()			=0; //[4]전체 데이터 수
		virtual void						total_row_count(INT32 var)	=0;
		virtual IArrayPtr<IPurchaseNo*>*	purchase_nums()				=0; //[?]구매번호 구조체 배열
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 12: Pickup Standby Cash Inventory - 구매 번호에 해당하는 아이템을 게임 내 수령 대기상태로 전환
	class IRequestPickupStandbyCashInventory : public IRequestParent
	{
	public:
		IRequestPickupStandbyCashInventory()			{}
		virtual ~IRequestPickupStandbyCashInventory()	{}

		//get,set
		virtual BYTE	item_expand_flag()				=0; //[1]Cash Inventory Item Expand Flags (fcs_constant.h의 "Table 11 Inquiry Cash Inventory Expand Flags" 참조)
		virtual void	item_expand_flag(BYTE var)		=0;
		virtual INT32	optional_world_no()				=0; //[4]Initialize 수행한 World No와 다른 World No로 조회할 경우 사용한다. 사용자 계정 경우 -1 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]계정 ID(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT64	purchase_no()					=0; //[8]구매 번호
		virtual void	purchase_no(INT64 var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponsePickupStandbyCashInventory : public IResponseParent		// 간소화 요청에 따른 인터페이스 구성 변경
	{
	public:
		IResponsePickupStandbyCashInventory()			{}
		virtual ~IResponsePickupStandbyCashInventory()	{}

		//get,set
		virtual PStr											callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void											callback_attribute(PStr var)	=0;
		virtual	INT32											total_row_count()				=0; //[4]전체 데이터 수
		virtual void											total_row_count(INT32 var)		=0;
		virtual INT64											purchase_no()					=0;	//[8]구매 번호
		virtual void											purchase_no(INT64 var)			=0;
		virtual INT32											user_no()						=0;	//[4]사용자 번호
		virtual void											user_no(INT32 var)				=0;
		virtual INT32											account_no()					=0;	//[4]계정 번호
		virtual void											account_no(INT32 var)			=0;
		virtual INT32											character_no()					=0; //[4]캐릭터번호
		virtual void											character_no(INT32 var)			=0;
		virtual INT32											world_no()						=0; //[4]월드 번호
		virtual void											world_no(INT32 var)				=0;
		virtual IArrayPtr<IPickupStandbyCashInventoryItem*>*	items()							=0; //[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 13: Complete Pickup Standby Cash Inventory - 구매 번호에 해당하는 아이템을 게임 내 수령 완료상태로 전환
	class IRequestCompletePickupStandbyCashInventory : public IRequestParent
	{
	public:
		IRequestCompletePickupStandbyCashInventory()			{}
		virtual ~IRequestCompletePickupStandbyCashInventory()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual INT32	account_no()					=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]Initialize 수행한 World No와 다른 World No로 조회할 경우 사용한다. 사용자 계정 경우 -1 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual INT32	character_no()					=0;	//[4]캐릭터 번호 (계정귀속인 경우 -1)
		virtual void	character_no(INT32 var)			=0;
		virtual INT64	purchase_no()					=0; //[8]주문 번호
		virtual void	purchase_no(INT64 var)			=0;
		virtual INT32	item_no()						=0;	//[4]아이템 번호(패키지 서브 아이템 번호)
		virtual void	item_no(INT32 var)				=0;
		virtual SHORT	pickup_quantity()				=0;	//[2]수령 수량
		virtual void	pickup_quantity(SHORT var)		=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		
	};
	class IResponseCompletePickupStandbyCashInventory : public IResponseParent
	{
	public:
		IResponseCompletePickupStandbyCashInventory()			{}
		virtual ~IResponseCompletePickupStandbyCashInventory()	{}

		//get,set
		virtual INT64	purchase_no()					=0; //[8]주문 번호
		virtual void	purchase_no(INT64 var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 14: Cancel Pickup Standby Cash Inventory - 구매 번호에 해당하는 아이템을 게임 내 수령 대기상태에서 취소
	class IRequestCancelPickupStandbyCashInventory : public IRequestParent
	{
	public:
		IRequestCancelPickupStandbyCashInventory()			{}
		virtual ~IRequestCancelPickupStandbyCashInventory()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual INT32	account_no()					=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]Initialize 수행한 World No와 다른 World No로 조회할 경우 사용한다. 사용자 계정 경우 -1 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual INT32	character_no()					=0;	//[4]캐릭터 번호 (계정귀속인 경우 -1)
		virtual void	character_no(INT32 var)			=0;
		virtual INT64	purchase_no()					=0; //[8]주문 번호
		virtual void	purchase_no(INT64 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		
	};
	class IResponseCancelPickupStandbyCashInventory : public IResponseParent
	{
	public:
		IResponseCancelPickupStandbyCashInventory()				{}
		virtual ~IResponseCancelPickupStandbyCashInventory()	{}

		//get,set
		virtual INT64	purchase_no()					=0; //[8]주문 번호
		virtual void	purchase_no(INT64 var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]요청시전달한속성값
		virtual void	callback_attribute(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 15: Use Storage - IBS 보관함 상품 사용
	class IRequestUseStorage : public IRequestParent
	{
	public:
		IRequestUseStorage()			{}
		virtual ~IRequestUseStorage()	{}
		
		//get,set
		virtual INT32	account_no()				=0; //[4]계정 번호
		virtual void	account_no(INT32 var)		=0;
		virtual INT32	game_code()					=0; //[4]게임 코드
		virtual void	game_code(INT32 var)		=0;
		virtual INT32	server_seq()				=0; //[4]게임 서버 순번(서버별 보관함 상품 사용 시, 그 외 -1)
		virtual void	server_seq(INT32 var)		=0;
		virtual PStr	client_ip()					=0; //[?]사용자 IP 주소
		virtual void	client_ip(PStr var)			=0;
		virtual INT32	storage_seq()				=0; //[4]보관함 순번
		virtual void	storage_seq(INT32 var)		=0;
		virtual INT32	storage_item_seq()			=0; //[4]보관함 상품 순번
		virtual void	storage_item_seq(INT32 var)	=0;
		virtual INT32	char_class()				=0; //[4]캐릭터 클래스(없으면 0)
		virtual void	char_class(INT32 var)		=0;
		virtual INT32	char_level()				=0; //[4]캐릭터 레벨(없으면 0)
		virtual void	char_level(INT32 var)		=0;
		virtual PStr	char_name()					=0; //[?]캐릭터 명
		virtual void	char_name(PStr var)			=0;
		virtual PStr	char_rank()					=0; //[?]캐릭터 랭크
		virtual void	char_rank(PStr var)			=0;
		virtual INT32	server_index()				=0; //[4]서버 번호
		virtual void	server_index(INT32 var)		=0;
	};
	class IResponseUseStorage : public IResponseParent
	{
	public:
		IResponseUseStorage()			{}
		virtual ~IResponseUseStorage()	{}
		
		//get,set
		virtual INT32	account_no()							=0; //[4]계정 번호
		virtual void	account_no(INT32 var)					=0;
		virtual INT32	ibs_result()							=0;	//[4]IBS 처리 결과값
		virtual void	ibs_result(INT32 var)					=0;
		virtual INT32	server_seq()							=0; //[4]게임 서버 순번 값
		virtual void	server_seq(INT32 var)					=0;
		virtual PStr	in_game_product_id()					=0; //[?]게임에서 사용하는 아이템 코드
		virtual void	in_game_product_id(PStr var)			=0;
		virtual INT32	product_seq()							=0; //[4]상품 번호
		virtual void	product_seq(INT32 var)					=0;
		virtual INT32	storage_seq()							=0; //[4]보관함 번호
		virtual void	storage_seq(INT32 var)					=0;
		virtual INT32	storage_item_seq()						=0; //[4]보관함 캐시 or 상품 번호
		virtual void	storage_item_seq(INT32 var)				=0;
		virtual INT32	property_count()						=0; //[4]속성 개수
		virtual void	property_count(INT32 var)				=0;
		virtual IArrayPtr<ISTItemProperty*>*	property_list()	=0; //[?]STItemProperty Structure 배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cash Inventory Step 16: Rollback Use Storage - IBS 보관함 사용 롤백
	class IRequestRollbackUseStorage : public IRequestParent
	{
	public:
		IRequestRollbackUseStorage()			{}
		virtual ~IRequestRollbackUseStorage()	{}
		
		//get,set
		virtual INT32	account_no()				=0; //[4]계정 번호
		virtual void	account_no(INT32 var)		=0;
		virtual INT32	game_code()					=0; //[4]게임 코드
		virtual void	game_code(INT32 var)		=0;
		virtual INT32	storage_seq()				=0; //[4]보관함 순번
		virtual void	storage_seq(INT32 var)		=0;
		virtual INT32	storage_item_seq()			=0; //[4]보관함 상품 순번
		virtual void	storage_item_seq(INT32 var)	=0;
	};
	class IResponseRollbackUseStorage : public IResponseParent
	{
	public:
		IResponseRollbackUseStorage()			{}
		virtual ~IResponseRollbackUseStorage()	{}
		
		//get,set
		virtual INT32	account_no()				=0; //[4]계정 번호
		virtual void	account_no(INT32 var)		=0;
		virtual INT32	ibs_result()				=0; //[4]IBS 처리 결과값
		virtual void	ibs_result(INT32 var)		=0;
	};


//## Advanced Biling - Cash Inventory : END
//#################################################################################################
//##
//#################################################################################################
//## Advanced Biling - Inquiry OData : START
//##
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Inquiry OData Step 1: Inquiry Service Metadata : OData에 대한 Metadata 조회
	class IRequestInquiryServiceMetadata : public IRequestParent
	{
	public:
		IRequestInquiryServiceMetadata()			{}
		virtual ~IRequestInquiryServiceMetadata()	{}

		//get,set
		virtual PStr	client_ip()				=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)		=0;
	};
	class IResponseInquiryServiceMetadata : public IResponseParent
	{
	public:
		IResponseInquiryServiceMetadata()			{}
		virtual ~IResponseInquiryServiceMetadata()	{}

		//get,set
		virtual PStr	json()			=0;	//[?]제공하고 있는 Metadata JSON 포멧
		virtual void	json(PStr var)	=0;
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Inquiry OData Step 2: Inquiry OData Service: OData 조회 (상품 정보)
	class IRequestInquiryODataService : public IRequestParent
	{
	public:
		IRequestInquiryODataService()			{}
		virtual ~IRequestInquiryODataService()	{}

		//get,set
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual BYTE	execute_method_type()			=0; //[1]조회할메소드타입(fcs_Constant.h - Table 16 Execute Method Type)
		virtual void	execute_method_type(BYTE var)	=0;
		virtual PStr	expand()						=0; //[?]Entity 확장(OData URL Conventions참고)(알수없을경우빈문자열) - http://www.odata.org/media/30002/OData%20URL%20Conventions.html
		virtual void	expand(PStr var)				=0;
		virtual PStr	filter()						=0; //[?]검색조건(OData URL Conventions참고)(알수없을경우빈문자열) - http://www.odata.org/media/30002/OData%20URL%20Conventions.html
		virtual void	filter(PStr var)				=0;
		virtual PStr	select()						=0; //[?]컬럼(OData URL Conventions참고)(알수없을경우빈문자열) - http://www.odata.org/media/30002/OData%20URL%20Conventions.html
		virtual void	select(PStr var)				=0;
		virtual PStr	order_by()						=0; //[?]정렬조건(OData URL Conventions참고)(알수없을경우빈문자열) - http://www.odata.org/media/30002/OData%20URL%20Conventions.html
		virtual void	order_by(PStr var)				=0;
		virtual INT32	page_index()					=0; //[4]페이지번호
		virtual void	page_index(INT32 var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터를확인할수있다.)
		virtual void	row_per_page(INT32 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseInquiryODataService : public IResponseParent
	{
	public:
		IResponseInquiryODataService()			{}
		virtual ~IResponseInquiryODataService()	{}

		//get,set
		virtual INT64	item_version()				=0; //[8]샵 아이템 버전
		virtual void	item_version(INT64 var)		=0;
		virtual INT32	total_count()				=0; //[4]전체 카운트
		virtual void	total_count(INT32 var)		=0;
		virtual PStr	json()						=0;	//[?]JSON 포멧
		virtual void	json(PStr var)				=0;
	};

//## Advanced Biling - Inquiry OData : END
//#################################################################################################
//##
//#################################################################################################
//## Advanced Biling - Cart & Wish Items : START
//##
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 1: Inquiry Cart Items : 쇼핑카트조회
	class IRequestInquiryCartItems : public IRequestParent
	{
	public:
		IRequestInquiryCartItems()			{}
		virtual ~IRequestInquiryCartItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	page_index()					=0; //[4]페이지번호
		virtual void	page_index(INT32 var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터확인)
		virtual void	row_per_page(INT32 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseInquiryCartItems : public IResponseParent
	{
	public:
		IResponseInquiryCartItems()			{}
		virtual ~IResponseInquiryCartItems()	{}

		//get,set
		virtual INT32	total_items_count()				=0; //[4]쇼핑카트수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<ICartItemInfo*>*	items()		=0;	//[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 2: Register Cart Items : 쇼핑카트상품등록
	class IRequestRegisterCartItems : public IRequestParent
	{
	public:
		IRequestRegisterCartItems()				{}
		virtual ~IRequestRegisterCartItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터확인)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRegisterItem*>*	items()		=0; //[?]쇼핑카트에등록할아이템구조체배열
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseRegisterCartItems : public IResponseParent
	{
	public:
		IResponseRegisterCartItems()			{}
		virtual ~IResponseRegisterCartItems()	{}

		//get,set
		virtual INT32	total_items_count()				=0; //[4]쇼핑카트수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<ICartItemInfo*>*	items()		=0; //[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 3: Modify Cart Items Quantity : 쇼핑카트아이템변경
	class IRequestModifyCartItemsQuantity : public IRequestParent
	{
	public:
		IRequestModifyCartItemsQuantity()			{}
		virtual ~IRequestModifyCartItemsQuantity()	{}

		//get,set
		virtual INT64	cart_no()						=0; //[8]카트번호
		virtual void	cart_no(INT64 var)				=0;
		virtual SHORT	purchase_quantity()				=0; //[2]주문수량
		virtual void	purchase_quantity(SHORT var)	=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseModifyCartItemsQuantity : public IResponseParent
	{
	public:
		IResponseModifyCartItemsQuantity()			{}
		virtual ~IResponseModifyCartItemsQuantity()	{}
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 4: Modify Cart Items Attribute : 쇼핑카트아이템변경
	class IRequestModifyCartItemsAttribute : public IRequestParent
	{
	public:
		IRequestModifyCartItemsAttribute()			{}
		virtual ~IRequestModifyCartItemsAttribute()	{}

		//get,set
		virtual INT64	cart_no()						=0; //[8]카트번호
		virtual void	cart_no(INT64 var)				=0;
		virtual PStr	attribute0()					=0; //[?]확장속성
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]확장속성
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]확장속성
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]확장속성
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]확장속성
		virtual void	attribute4(PStr var)			=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;

	};
	class IResponseModifyCartItemsAttribute : public IResponseParent
	{
	public:
		IResponseModifyCartItemsAttribute()			{}
		virtual ~IResponseModifyCartItemsAttribute()	{}
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 5: Remove Cart Items : 쇼핑카트아이템삭제
	class IRequestRemoveCartItems : public IRequestParent
	{
	public:
		IRequestRemoveCartItems()			{}
		virtual ~IRequestRemoveCartItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터확인)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRequestNo*>*	items()			=0; //[?]쇼핑카트에서삭제할카트구조체배열
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseRemoveCartItems : public IResponseParent
	{
	public:
		IResponseRemoveCartItems()			{}
		virtual ~IResponseRemoveCartItems()	{}

		//get,set
		virtual	INT32	total_items_count()				=0; //[4]쇼핑카트수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<ICartItemInfo*>*	items()		=0; //[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 6: Remove Cart : 쇼핑카트초기화
	class IRequestRemoveCart : public IRequestParent
	{
	public:
		IRequestRemoveCart()			{}
		virtual ~IRequestRemoveCart()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseRemoveCart : public IResponseParent
	{
	public:
		IResponseRemoveCart()			{}
		virtual ~IResponseRemoveCart()	{}
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 7: Cart Items Transfer Wish Items : 위시아이템으로 쇼핑카트 아이템 이동
	class IRequestCartItemsTransferWishItems : public IRequestParent
	{
	public:
		IRequestCartItemsTransferWishItems()			{}
		virtual ~IRequestCartItemsTransferWishItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터확인)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRequestNo*>*	items()			=0; //[?]쇼핑카트에서 이동할 카트 구조체 배열
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseCartItemsTransferWishItems : public IResponseParent
	{
	public:
		IResponseCartItemsTransferWishItems()			{}
		virtual ~IResponseCartItemsTransferWishItems()	{}

		//get,set
		virtual	INT32	total_items_count()				=0; //[4]남은쇼핑카트수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<ICartItemInfo*>*	items()		=0; //[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 8: Inquiry Wish Items : 위시아이템조회
	class IRequestInquiryWishItems : public IRequestParent
	{
	public:
		IRequestInquiryWishItems()			{}
		virtual ~IRequestInquiryWishItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	page_index()					=0; //[4]페이지번호
		virtual void	page_index(INT32 var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터확인)
		virtual void	row_per_page(INT32 var)			=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
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
		virtual	INT32	total_items_count()				=0; //[4]위시아이템총수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IWishItemInfo*>*	items()		=0; //[?]아이템구조체배열
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 9: Register Wish Items : Wish 리스트상품등록
	class IRequestRegisterWishItems : public IRequestParent
	{
	public:
		IRequestRegisterWishItems()				{}
		virtual ~IRequestRegisterWishItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터확인)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRegisterItem*>* items()		=0; //[?]위시리스트에등록할아이템구조체배열
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
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
		virtual	INT32	total_items_count()				=0; //[4]위시아이템총수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IWishItemInfo*>*	items()		=0; //[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 10: Remove Wish Items : 위시 아이템 변경
	class IRequestRemoveWishItems : public IRequestParent
	{
	public:
		IRequestRemoveWishItems()			{}
		virtual ~IRequestRemoveWishItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터확인)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRequestNo*>*	items()			=0; //[?]위시리스트에서삭제할카트구조체배열
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
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
		virtual	INT32	total_items_count()				=0; //[4]위시아이템전체수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IWishItemInfo*>*	items()		=0; //[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 11: Remove Wish : 위시 아이템 초기화
	class IRequestRemoveWish : public IRequestParent
	{
	public:
		IRequestRemoveWish()			{}
		virtual ~IRequestRemoveWish()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseRemoveWish : public IResponseParent
	{
	public:
		IResponseRemoveWish()			{}
		virtual ~IResponseRemoveWish()	{}
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Cart & Wish Items Step 12: Wish Items Transfer Cart Items : 쇼핑카트로 위시 아이템 이동
	class IRequestWishItemsTransferCartItems : public IRequestParent
	{
	public:
		IRequestWishItemsTransferCartItems()			{}
		virtual ~IRequestWishItemsTransferCartItems()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual INT32	row_per_page()					=0; //[4]페이지당데이터개수(0이하또는 0x7FFFFFFF이면전체데이터확인)
		virtual void	row_per_page(INT32 var)			=0;
		virtual IArrayPtr<IRequestNo*>*	items()			=0; //[?]위시리스트에서 이동할 구조체 배열
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseWishItemsTransferCartItems : public IResponseParent
	{
	public:
		IResponseWishItemsTransferCartItems()			{}
		virtual ~IResponseWishItemsTransferCartItems()	{}

		//get,set
		virtual	INT32	total_items_count()				=0; //[4]남은쇼핑카트수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IWishItemInfo*>*	items()		=0; //[?]아이템구조체배열
	};

//## Advanced Biling - Cart & Wish Items : END
//#################################################################################################
//##
//#################################################################################################
//## Advanced Biling - Order : START
//##	GP2.0 아이템샵시스템에서는등록된아이템속성에따라서사용자또는캐릭터단위로 Cash Inventory를구성할수있다.
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 1: Shop Direct Purchase Item : 바로구매
	class IRequestShopDirectPurchaseItem : public IRequestParent
	{
	public:
		IRequestShopDirectPurchaseItem()			{}
		virtual ~IRequestShopDirectPurchaseItem()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]성별또는직업형식(사용안할경우99)
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]게임레벨
		virtual void	game_level(INT32 var)			=0;
		virtual PStr	order_id()						=0; //[?]게임에서생성한유니크한주문번호(World별유니크보장필요)
		virtual void	order_id(PStr var)				=0;
		virtual INT32	category_no()					=0; //[4]카테고리번호
		virtual void	category_no(INT32 var)			=0;
		virtual INT32	item_no()						=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)				=0;
		virtual PStr	item_type()						=0; //[?]아이템타입
		virtual void	item_type(PStr var)				=0;
		virtual PStr	sale_type()						=0; //[?]판매타입
		virtual void	sale_type(PStr var)				=0;
		virtual SHORT	order_quantity()				=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)		=0;		
		virtual INT32	purchase_price()				=0;	//[4]구매 금액 (할인룰 있는경우는 할인 적용된 금액)
		virtual void	purchase_price(INT32 var)		=0;
		virtual PStr	item_sale_type()				=0; //[?]아이템판매유형
		virtual void	item_sale_type(PStr var)		=0;
		virtual PStr	purchase_type()					=0; //[?]구매타입
		virtual void	purchase_type(PStr var)			=0;
		virtual BYTE	inventory_status()				=0; //[1]인벤토리상태(즉시수령:kISImmediately(0x1F), 픽업을통한수령:kISPickup(0x05))
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	attribute0()					=0; //[?]속성(클라라의 Property0)
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]속성(클라라의 Property1)
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]속성(클라라의 Property2)
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]속성(클라라의 Property3)
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]속성(클라라의 Property4)
		virtual void	attribute4(PStr var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]설명
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]클라이언트IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopDirectPurchaseItem : public IResponseParent
	{
	public:
		IResponseShopDirectPurchaseItem()			{}
		virtual ~IResponseShopDirectPurchaseItem()	{}

		//get,set
		virtual	INT32	total_items_count()				=0; //[4]총주문수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IApprovalItem*>*	items()		=0; //[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 2: Shop Direct Purchase Item by Bind Attribute : 아이템 귀속 형태에 따른 바로구매
	class IRequestShopDirectPurchaseItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestShopDirectPurchaseItemByBindAttribute()				{}
		virtual ~IRequestShopDirectPurchaseItemByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]계정 ID(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]성별또는직업형식(사용안할경우99)
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]게임레벨
		virtual void	game_level(INT32 var)			=0;
		virtual PStr	order_id()						=0; //[?]게임에서생성한유니크한주문번호(World별유니크보장필요)
		virtual void	order_id(PStr var)				=0;
		virtual INT32	category_no()					=0; //[4]카테고리번호
		virtual void	category_no(INT32 var)			=0;
		virtual INT32	item_no()						=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)				=0;
		virtual PStr	item_type()						=0; //[?]아이템타입
		virtual void	item_type(PStr var)				=0;
		virtual PStr	sale_type()						=0; //[?]판매타입
		virtual void	sale_type(PStr var)				=0;
		virtual SHORT	order_quantity()				=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)		=0;		
		virtual INT32	purchase_price()				=0;	//[4]구매 금액 (할인룰 있는경우는 할인 적용된 금액)
		virtual void	purchase_price(INT32 var)		=0;
		virtual PStr	item_sale_type()				=0; //[?]아이템판매유형
		virtual void	item_sale_type(PStr var)		=0;
		virtual PStr	purchase_type()					=0; //[?]구매타입
		virtual void	purchase_type(PStr var)			=0;
		virtual BYTE	inventory_status()				=0; //[1]인벤토리상태(즉시수령:kISImmediately(0x1F), 픽업을통한수령:kISPickup(0x05))
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	attribute0()					=0; //[?]속성(클라라의 Property0)
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]속성(클라라의 Property1)
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]속성(클라라의 Property2)
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]속성(클라라의 Property3)
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]속성(클라라의 Property4)
		virtual void	attribute4(PStr var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]설명
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]클라이언트IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopDirectPurchaseItemByBindAttribute : public IResponseParent
	{
	public:
		IResponseShopDirectPurchaseItemByBindAttribute()			{}
		virtual ~IResponseShopDirectPurchaseItemByBindAttribute()	{}

		//get,set
		virtual	INT32	total_items_count()				=0; //[4]총주문수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IApprovalItem*>*	items()		=0; //[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 3: Shop Purchase Cart Items : 쇼핑카트구매
	class IRequestShopPurchaseCartItems : public IRequestParent
	{
	public:
		IRequestShopPurchaseCartItems()				{}
		virtual ~IRequestShopPurchaseCartItems()	{}
		
		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]성별또는직업형식
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]게임레벨
		virtual void	game_level(INT32 var)			=0;
		virtual PStr	order_id()						=0; //[?]게임에서생성한유니크한주문번호(World별유니크보장필요)
		virtual void	order_id(PStr var)				=0;
		virtual IArrayPtr<ICartItem*>* items()			=0; //[?]쇼핑카트에서주문할구조체배열
		virtual BYTE	inventory_status()				=0; //[1]인벤토리상태(즉시수령:0x1E, 픽업을통한수령:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]설명
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]클라이언트IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopPurchaseCartItems : public IResponseParent
	{
	public:
		IResponseShopPurchaseCartItems()			{}
		virtual ~IResponseShopPurchaseCartItems()	{}
		
		//get,set
		virtual INT32	total_items_count()					=0; //[4]총주문수량
		virtual void	total_items_count(INT32 var)		=0;
		virtual	IArrayPtr<IApprovalItem*>* items()			=0; //[?]아이템구조체배열
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 4: Shop Direct Gift Item : 바로선물
	class IRequestShopDirectGiftItem : public IRequestParent
	{
	public:
		IRequestShopDirectGiftItem()			{}
		virtual ~IRequestShopDirectGiftItem()	{}
		
		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]성별또는직업형식
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]게임레벨
		virtual void	game_level(INT32 var)			=0;
		virtual INT32	receive_user_no()				=0; //[4]선물받을사용자번호(알수없을경우 -1)
		virtual void	receive_user_no(INT32 var)		=0;
		virtual PStr	receive_user_id()				=0; //[?]선물받을사용자아이디(알수없을경우빈문자열)
		virtual void	receive_user_id(PStr var)		=0;
		virtual INT32	receive_word_no()				=0; //[4]선물받을월드번호(알수없을경우 -1)
		virtual void	receive_word_no(INT32 var)		=0;
		virtual PStr	receive_word_key()				=0; //[?]선물받을월드키(알수없을경우빈문자열)
		virtual void	receive_word_key(PStr var)		=0;
		virtual INT32	receive_character_no()			=0; //[4]선물받을캐릭터번호(알수없을경우 -1)
		virtual void	receive_character_no(INT32 var)	=0;
		virtual PStr	receive_character_id()			=0; //[?]선물받을캐릭터아이디(알수없을경우빈문자열)
		virtual void	receive_character_id(PStr var)	=0;
		virtual PStr	send_message()					=0; //[?]선물메시지
		virtual void	send_message(PStr var)			=0;
		virtual PStr	order_id()						=0; //[?]게임에서생성한유니크한주문번호(World별유니크보장필요)
		virtual void	order_id(PStr var)				=0;
		virtual INT32	category_no()					=0; //[4]카테고리번호
		virtual void	category_no(INT32 var)			=0;
		virtual INT32	item_no()						=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)				=0;
		virtual PStr	item_type()						=0; //[?]아이템타입
		virtual void	item_type(PStr var)				=0;
		virtual PStr	sale_type()						=0; //[?]판매타입
		virtual void	sale_type(PStr var)				=0;
		virtual SHORT	order_quantity()				=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)		=0;
		virtual INT32	purchase_price()				=0;	//[4]구매 금액 (할인룰 있는경우는 할인 적용된 금액)
		virtual void	purchase_price(INT32 var)		=0;
		virtual PStr	item_sale_type()				=0; //[?]아이템판매유형
		virtual void	item_sale_type(PStr var)		=0;
		virtual PStr	purchase_type()					=0; //[?]구매타입
		virtual void	purchase_type(PStr var)			=0;
		virtual BYTE	inventory_status()				=0; //[1]인벤토리상태(즉시수령:0x1E, 픽업을통한수령:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	attribute0()					=0; //[?]속성
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]속성
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]속성
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]속성
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]속성
		virtual void	attribute4(PStr var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]설명
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]클라이언트IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopDirectGiftItem : public IResponseParent
	{
	public:
		IResponseShopDirectGiftItem()			{}
		virtual ~IResponseShopDirectGiftItem()	{}
		
		//get,set
		virtual INT32	total_items_count()				=0; //[4]총주문수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual	IArrayPtr<IApprovalItem*>* items()		=0; //[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 5: Shop Direct Gift Item by Bind Attribute : 아이템 귀속 형태에 따른 바로선물
	class IRequestShopDirectGiftItemByBindAttribute : public IRequestParent
	{
	public:
		IRequestShopDirectGiftItemByBindAttribute()				{}
		virtual ~IRequestShopDirectGiftItemByBindAttribute()	{}
		
		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]계정 ID(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]성별또는직업형식
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]게임레벨
		virtual void	game_level(INT32 var)			=0;
		virtual INT32	receive_user_no()				=0; //[4]선물 받을 사용자 번호(알수없을경우 -1)
		virtual void	receive_user_no(INT32 var)		=0;
		virtual PStr	receive_user_id()				=0; //[?]선물 받을사용자ID(알수없을경우빈문자열)
		virtual void	receive_user_id(PStr var)		=0;
		virtual INT32	receive_account_no()			=0; //[4]선물 받을 계정 번호(알수없을경우 -1)
		virtual void	receive_account_no(INT32 var)	=0;
		virtual PStr	receive_account_id()			=0; //[?]선물 받을 계정 ID(알수없을경우빈문자열)
		virtual void	receive_account_id(PStr var)	=0;
		virtual INT32	receive_word_no()				=0; //[4]선물받을월드번호(알수없을경우 -1)
		virtual void	receive_word_no(INT32 var)		=0;
		virtual PStr	receive_word_key()				=0; //[?]선물받을월드키(알수없을경우빈문자열)
		virtual void	receive_word_key(PStr var)		=0;
		virtual INT32	receive_character_no()			=0; //[4]선물받을캐릭터번호(알수없을경우 -1)
		virtual void	receive_character_no(INT32 var)	=0;
		virtual PStr	receive_character_id()			=0; //[?]선물받을캐릭터아이디(알수없을경우빈문자열)
		virtual void	receive_character_id(PStr var)	=0;
		virtual PStr	send_message()					=0; //[?]선물메시지
		virtual void	send_message(PStr var)			=0;
		virtual PStr	order_id()						=0; //[?]게임에서생성한유니크한주문번호(World별유니크보장필요)
		virtual void	order_id(PStr var)				=0;
		virtual INT32	category_no()					=0; //[4]카테고리번호
		virtual void	category_no(INT32 var)			=0;
		virtual INT32	item_no()						=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)				=0;
		virtual PStr	item_type()						=0; //[?]아이템타입
		virtual void	item_type(PStr var)				=0;
		virtual PStr	sale_type()						=0; //[?]판매타입
		virtual void	sale_type(PStr var)				=0;
		virtual SHORT	order_quantity()				=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)		=0;
		virtual INT32	purchase_price()				=0;	//[4]구매 금액 (할인룰 있는경우는 할인 적용된 금액)
		virtual void	purchase_price(INT32 var)		=0;
		virtual PStr	item_sale_type()				=0; //[?]아이템판매유형
		virtual void	item_sale_type(PStr var)		=0;
		virtual PStr	purchase_type()					=0; //[?]구매타입
		virtual void	purchase_type(PStr var)			=0;
		virtual BYTE	inventory_status()				=0; //[1]인벤토리상태(즉시수령:0x1E, 픽업을통한수령:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	attribute0()					=0; //[?]속성
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]속성
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]속성
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]속성
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]속성
		virtual void	attribute4(PStr var)			=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]설명
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]클라이언트IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopDirectGiftItemByBindAttribute : public IResponseParent
	{
	public:
		IResponseShopDirectGiftItemByBindAttribute()			{}
		virtual ~IResponseShopDirectGiftItemByBindAttribute()	{}
		
		//get,set
		virtual INT32	total_items_count()				=0; //[4]총주문수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual	IArrayPtr<IApprovalItem*>* items()		=0; //[?]아이템구조체배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Order Step 6: Shop Gift Cart Items : 쇼핑카트선물
	class IRequestShopGiftCartItems : public IRequestParent
	{
	public:
		IRequestShopGiftCartItems()				{}
		virtual ~IRequestShopGiftCartItems()	{}
		
		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual BYTE	gender_or_class_type()			=0; //[1]성별또는직업형식
		virtual void	gender_or_class_type(BYTE var)	=0;
		virtual INT32	game_level()					=0; //[4]게임레벨
		virtual void	game_level(INT32 var)			=0;
		virtual INT32	receive_user_no()				=0; //[4]선물받을사용자번호(알수없을경우 -1)
		virtual void	receive_user_no(INT32 var)		=0;
		virtual PStr	receive_user_id()				=0; //[?]선물받을사용자아이디(알수없을경우빈문자열)
		virtual void	receive_user_id(PStr var)		=0;
		virtual INT32	receive_word_no()				=0; //[4]선물받을월드번호(알수없을경우 -1)
		virtual void	receive_word_no(INT32 var)		=0;
		virtual PStr	receive_word_key()				=0; //[?]선물받을월드키(알수없을경우빈문자열)
		virtual void	receive_word_key(PStr var)		=0;
		virtual INT32	receive_character_no()			=0; //[4]선물받을캐릭터번호(알수없을경우 -1)
		virtual void	receive_character_no(INT32 var)	=0;
		virtual PStr	receive_character_id()			=0; //[?]선물받을캐릭터아이디(알수없을경우빈문자열)
		virtual void	receive_character_id(PStr var)	=0;
		virtual PStr	send_message()					=0; //[?]선물메시지
		virtual void	send_message(PStr var)			=0;
		virtual PStr	order_id()						=0; //[?]게임에서생성한유니크한주문번호(World별유니크보장필요)
		virtual void	order_id(PStr var)				=0;
		virtual IArrayPtr<ICartItem*>* items()			=0; //[?]쇼핑카트에서선물할구조체배열
		virtual BYTE	inventory_status()				=0; //[1]인벤토리상태(즉시수령:0x1E, 픽업을통한수령:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	description()					=0; //[?]설명
		virtual void	description(PStr var)			=0;
		virtual PStr	client_ip()						=0; //[?]클라이언트IP주소
		virtual void	client_ip(PStr var)				=0;
	};
	class IResponseShopGiftCartItems : public IResponseParent
	{
	public:
		IResponseShopGiftCartItems()			{}
		virtual ~IResponseShopGiftCartItems()	{}
		
		//get,set
		virtual INT32	total_items_count()				=0; //[?]총주문수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual	IArrayPtr<IApprovalItem*>* items()		=0; //[?]아이템구조체배열
	};

//## Advanced Biling - Order : END
//#################################################################################################
//##
//#################################################################################################
//## Coupon : START
//##
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Coupon Step 1: Check Coupon : 쿠폰 체크
	class IRequestCheckCoupon : public IRequestParent
	{
	public:
		IRequestCheckCoupon()			{}
		virtual ~IRequestCheckCoupon()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	serial()						=0; //[?]쿠폰시리얼
		virtual void	serial(PStr var)				=0;
		virtual PStr	pii()							=0;	//[?]PII
		virtual void	pii(PStr var)					=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseCheckCoupon : public IResponseParent
	{
	public:
		IResponseCheckCoupon()			{}
		virtual ~IResponseCheckCoupon()	{}

		//get,set
		virtual bool	can_use()								=0; //[1]사용가능 여부
		virtual void	can_use(bool var)						=0;
		virtual INT32	promotion_no()							=0;	//[4]프로모션 번호
		virtual void	promotion_no(INT32 var)					=0;
		virtual PStr	promotion_name()						=0;	//[?]프로모션 이름
		virtual void	promotion_name(PStr var)				=0;
		virtual INT64	promotion_begin_datetime()				=0; //[8]프로모션 시작일
		virtual void	promotion_begin_datetime(INT64 var)		=0;
		virtual INT64	promotion_end_datetime()				=0; //[8]프로모션 종료일
		virtual void	promotion_end_datetime(INT64 var)		=0;
		virtual PStr	description()							=0;	//[?]설명
		virtual void	description(PStr var)					=0;
		virtual INT32	total_items_count()						=0;	//[?]총주문수량
		virtual void	total_items_count(INT32 var)			=0;
		virtual IArrayPtr<ICouponItem*>*	items()				=0;	//[?]승인구조체 배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Coupon Step 2: Check Coupon by Bind Attribute : 아이템 귀속 형태에 따른 쿠폰 체크
	class IRequestCheckCouponByBindAttribute : public IRequestParent
	{
	public:
		IRequestCheckCouponByBindAttribute()			{}
		virtual ~IRequestCheckCouponByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자 ID(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]계정 ID(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	serial()						=0; //[?]쿠폰시리얼
		virtual void	serial(PStr var)				=0;
		virtual PStr	pii()							=0;	//[?]PII
		virtual void	pii(PStr var)					=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseCheckCouponByBindAttribute : public IResponseParent
	{
	public:
		IResponseCheckCouponByBindAttribute()			{}
		virtual ~IResponseCheckCouponByBindAttribute()	{}

		//get,set
		virtual bool	can_use()								=0; //[1]사용가능 여부
		virtual void	can_use(bool var)						=0;
		virtual INT32	promotion_no()							=0;	//[4]프로모션 번호
		virtual void	promotion_no(INT32 var)					=0;
		virtual PStr	promotion_name()						=0;	//[?]프로모션 이름
		virtual void	promotion_name(PStr var)				=0;
		virtual INT64	promotion_begin_datetime()				=0; //[8]프로모션 시작일
		virtual void	promotion_begin_datetime(INT64 var)		=0;
		virtual INT64	promotion_end_datetime()				=0; //[8]프로모션 종료일
		virtual void	promotion_end_datetime(INT64 var)		=0;
		virtual PStr	description()							=0;	//[?]설명
		virtual void	description(PStr var)					=0;
		virtual INT32	total_items_count()						=0;	//[?]총주문수량
		virtual void	total_items_count(INT32 var)			=0;
		virtual IArrayPtr<ICouponItem*>*	items()				=0;	//[?]승인구조체 배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Coupon Step 3: Use Coupon : 쿠폰 사용
	class IRequestUseCoupon : public IRequestParent
	{
	public:
		IRequestUseCoupon()				{}
		virtual ~IRequestUseCoupon()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자아이디(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	serial()						=0; //[?]쿠폰시리얼
		virtual void	serial(PStr var)				=0;
		virtual PStr	order_id()						=0; //[?]게임에서생성한유니크한주문번호(World별유니크보장필요)
		virtual void	order_id(PStr var)				=0;
		virtual BYTE	inventory_status()				=0; //[1]인벤토리상태(즉시수령:0x1E, 픽업을통한수령:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseUseCoupon : public IResponseParent
	{
	public:
		IResponseUseCoupon()			{}
		virtual ~IResponseUseCoupon()	{}

		//get,set
		virtual INT32	total_items_count()				=0;	//[?]총주문수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IApprovalItem*>*	items()		=0;	//[?]승인구조체 배열
	};

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Coupon Step 4: Use Coupon by Bind Attribute : 아이템 귀속 형태에 따른 쿠폰 사용
	class IRequestUseCouponByBindAttribute : public IRequestParent
	{
	public:
		IRequestUseCouponByBindAttribute()			{}
		virtual ~IRequestUseCouponByBindAttribute()	{}

		//get,set
		virtual INT32	user_no()						=0;	//[4]사용자 번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자 ID(알수없을경우빈문자열) : optional
		virtual void	user_id(PStr var)				=0;
		virtual INT32	account_no()					=0;	//[4]계정 번호
		virtual void	account_no(INT32 var)			=0;
		virtual PStr	account_id()					=0; //[?]계정 ID(알수없을경우빈문자열) : optional
		virtual void	account_id(PStr var)			=0;
		virtual INT32	optional_world_no()				=0; //[4]세팅을 안할 경우 -1이 설정되며 FCSAdapter.xml의 world_no 값이 반영됨 : optional
		virtual void	optional_world_no(INT32 var)	=0;
		virtual PStr	world_key()						=0; //[?]게임정의 서버키(알수없을경우빈문자열) : optional
		virtual void	world_key(PStr va)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터번호(알수없거나 또는 사용자경우 0이하값) : optional
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_id()					=0; //[?]캐릭터아이디(알수없을경우빈문자열) : optional
		virtual void	character_id(PStr var)			=0;
		virtual PStr	serial()						=0; //[?]쿠폰시리얼
		virtual void	serial(PStr var)				=0;
		virtual PStr	order_id()						=0; //[?]게임에서생성한유니크한주문번호(World별유니크보장필요)
		virtual void	order_id(PStr var)				=0;
		virtual BYTE	inventory_status()				=0; //[1]인벤토리상태(즉시수령:0x1E, 픽업을통한수령:0x05)
		virtual void	inventory_status(BYTE var)		=0;
		virtual PStr	callback_attribute()			=0; //[?]게임서버에전달된속성값
		virtual void	callback_attribute(PStr var)	=0;
		virtual PStr	client_ip()						=0;	//[?]사용자 IP주소
		virtual void	client_ip(PStr var)				=0;
	};

	class IResponseUseCouponByBindAttribute : public IResponseParent
	{
	public:
		IResponseUseCouponByBindAttribute()				{}
		virtual ~IResponseUseCouponByBindAttribute()	{}

		//get,set
		virtual INT32	total_items_count()				=0;	//[?]총주문수량
		virtual void	total_items_count(INT32 var)	=0;
		virtual IArrayPtr<IApprovalItem*>*	items()		=0;	//[?]승인구조체 배열
	};

//## Coupon : END
//#################################################################################################
//##
//#################################################################################################
//## SUB DTO : START
//##
	// 아이템 정보
	class IRequestItem : public IObject
	{
	public:
		IRequestItem()			{}
		virtual ~IRequestItem()	{}

		//get,set
		virtual PStr	item_key()				=0; //[?]게임 아이템 관리 값
		virtual void	item_key(PStr var)		=0;
		virtual INT32	item_cost()				=0; //[4]아이템 원가
		virtual void	item_cost(INT32 var)	=0;
		virtual INT32	item_price()			=0; //[4]아이템 구매가격
		virtual void	item_price(INT32 var)	=0;
		virtual BYTE	sales_type()			=0;	//[1]아이템 구입타입
		virtual void	sales_type(BYTE var)	=0;
		virtual bool	is_trade()				=0; //[1]거래가능 여부(1-거래가능, 0-불가능)
		virtual void	is_trade(bool var)		=0;
	};

	// 아이템 승인 정보
	class IResponseApprovalItem : public IObject
	{
	public:
		IResponseApprovalItem()				{}
		virtual ~IResponseApprovalItem()	{}

	public:
		virtual PStr	product_key()			=0;	//[?]게임 아이템 관리 값
		virtual void	product_key(PStr var)	=0;
		virtual INT32	purchase_no()			=0; //[4]구매승인 번호
		virtual void	purchase_no(INT32 var)	=0;
	};

	
	// 아이템 승인 정보
	class IPurchaseItem : public IObject
	{
	public:
		IPurchaseItem()				{}
		virtual ~IPurchaseItem()	{}

	public:
		virtual INT32	product_no()			=0;	//[?]아이템 번호
		virtual void	product_no(INT32 var)	=0;
		virtual INT32	purchase_no()			=0; //[4]구매승인 번호
		virtual void	purchase_no(INT32 var)	=0;
	};

	// Purchase No Structure
	class IPurchaseNo : public IObject
	{
	public:
		IPurchaseNo()			{}
		virtual ~IPurchaseNo()	{}

		//get,set
		virtual INT64	purchase_no()				=0; //[8]구매번호
		virtual void	purchase_no(INT64 var)		=0;
	};

	// Response Purchase Item Structure : 아이템 구매 내역 정보
	class IResponsePurchaseItem : public IObject
	{
	public:
		IResponsePurchaseItem()				{}
		virtual ~IResponsePurchaseItem()	{}

		virtual INT32	purchase_no()					=0; //[4]구매 승인번호
		virtual void	purchase_no(INT32 var)			=0;
		virtual BYTE	purchase_status()				=0; //[1]주문상태 값
		virtual void	purchase_status(BYTE var)		=0;
		virtual INT32	user_no()						=0; //[4]사용자번호
		virtual void	user_no(INT32 var)				=0;
		virtual PStr	user_id()						=0; //[?]사용자ID
		virtual void	user_id(PStr var)				=0;
		virtual PStr	product_key()					=0; //[?]게임 아이템 관리 값
		virtual void	product_key(PStr var)			=0;
		virtual PStr	order_id()						=0; //[?]주문번호
		virtual void	order_id(PStr var)				=0;
		virtual PStr	purchase_type()					=0; //[?]구매타입
		virtual void	purchase_type(PStr var)			=0;
		virtual BYTE	sales_type()					=0; //[1]판매유형
		virtual void	sales_type(BYTE var)			=0;
		virtual INT32	purchase_cost()					=0; //[4]구매상품 원가
		virtual void	purchase_cost(INT32 var)		=0;
		virtual INT32	purchase_quantity()				=0; //[4]주문수량
		virtual void	purchase_quantity(INT32 var)	=0;
		virtual INT32	purchase_amount()				=0; //[4]구매금액
		virtual void	purchase_amount(INT32 var)		=0;
		virtual bool	is_trade()						=0; //[1]거래가능 여부
		virtual void	is_trade(bool var)				=0;
		virtual PStr	service_code()					=0; //[?]서비스코드
		virtual void	service_code(PStr var)			=0;
		virtual INT32	world_no()						=0; //[4]월드번호
		virtual void	world_no(INT32 var)				=0;
		virtual INT32	character_no()					=0; //[4]캐릭터 번호
		virtual void	character_no(INT32 var)			=0;
		virtual PStr	character_name()				=0; //[?]캐릭터 이름
		virtual void	character_name(PStr var)		=0;
		virtual INT32	game_level()					=0; //[4]게임레벨
		virtual void	game_level(INT32 var)			=0;
		virtual INT32	receive_world_no()				=0; //[4]선물 받은 월드번호
		virtual void	receive_world_no(INT32 var)		=0;
		virtual INT32	receive_character_no()			=0; //[4]선물 받은 캐릭터 번호
		virtual void	receive_character_no(INT32 var)	=0;
		virtual PStr	receive_character_name()		=0; //[?]선물 받은 캐릭터 이름
		virtual void	receive_character_name(PStr var)=0;
		virtual PStr	message()						=0; //[?]메시지
		virtual void	message(PStr var)				=0;
		virtual INT64	register_datetime()				=0; //[8]등록일
		virtual void	register_datetime(INT64 var)	=0;
		virtual INT64	modify_datetime()				=0; //[8]수정일
		virtual void	modify_datetime(INT64 var)		=0;
		virtual PStr	client_ip()						=0; //[?]접속IP 주소
		virtual void	client_ip(PStr var)				=0;
		virtual PStr	standard_country_code()			=0; //[?]표준 국가코드
		virtual void	standard_country_code(PStr var)	=0;
	};

	// Response Flat Rate Payment Info Structure
	class IResponseFlatRatePaymentInfo : public IObject
	{
	public:
		IResponseFlatRatePaymentInfo()			{}
		virtual ~IResponseFlatRatePaymentInfo()	{}

		virtual INT32	use_flat_rate_no()			=0; //[4]정액 사용번호
		virtual void	use_flat_rate_no(INT32 var)	=0;
		virtual INT32	world_no()					=0; //[4]월드번호
		virtual void	world_no(INT32 var)			=0;
		virtual INT64	begin_datetime()			=0; //[8]시작 날짜(Ticks)
		virtual void	begin_datetime(INT64 var)	=0;
		virtual INT64	end_datetime()				=0; //[8]종료 날짜(Ticks)
		virtual void	end_datetime(INT64 var)		=0;
		virtual PStr	use_status()				=0; //[?]요금제 상태 정보 (fcs_constant.h의 "Table 6 Authorization Use Status Type" 참조)
		virtual void	use_status(PStr var)		=0;
	};

	// Response Coupon Item Structure : 쿠폰 아이템 구조체
	class ICouponItem : public IObject
	{
	public:
		ICouponItem()				{}
		virtual ~ICouponItem()		{}

		//get,set
		virtual PStr	service_code()				=0; //[?]서비스코드
		virtual void	service_code(PStr var)		=0;
		virtual INT32	item_no()					=0; //[4]아이템번호
		virtual void	item_no(INT32 var)			=0;
		virtual PStr	item_name()					=0; //[?]아이템이름
		virtual void	item_name(PStr var)			=0;
		virtual PStr	item_code()					=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)			=0;
		virtual PStr	item_type()					=0; //[?]아이템타입
		virtual void	item_type(PStr var)			=0;
		virtual PStr	item_sale_type()			=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)	=0;
		virtual bool	is_include_bonus()			=0; //[1]보너스포함여부
		virtual void	is_include_bonus(bool var)	=0;
		virtual INT32	item_cost()					=0; //[4]아이템원가
		virtual void	item_cost(INT32 var)		=0;
		virtual INT32	item_hour()					=0; //[4]기간제아이템일경우아이템유효기간
		virtual void	item_hour(INT32 var)		=0;
		virtual SHORT	item_quantity()				=0;	//[2]아이템구성수량
		virtual void	item_quantity(SHORT var)	=0;
		virtual INT32	total_quantity()			=0; //[4]총구성수량
		virtual void	total_quantity(INT32 var)	=0;
		virtual SHORT	reorder_term()				=0;	//[2]재주문가능시간(0 이면 무제한)
		virtual void	reorder_term(SHORT var)		=0;
		virtual BYTE	reorder_count()				=0;	//[1]재주문가능횟수(0 이면 무제한)
		virtual void	reorder_count(BYTE var)		=0;
		virtual PStr	attribute0()				=0; //[?]확장속성
		virtual void	attribute0(PStr var)		=0;
		virtual PStr	attribute1()				=0; //[?]확장속성
		virtual void	attribute1(PStr var)		=0;
		virtual PStr	attribute2()				=0; //[?]확장속성
		virtual void	attribute2(PStr var)		=0;
		virtual PStr	attribute3()				=0; //[?]확장속성
		virtual void	attribute3(PStr var)		=0;
		virtual PStr	attribute4()				=0; //[?]확장속성
		virtual void	attribute4(PStr var)		=0;
	};

	// Response Coupon Item Structure : 쿠폰 아이템 구조체
	class IApprovalItem : public IObject
	{
	public:
		IApprovalItem(){}
		virtual ~IApprovalItem(){}

		//get,set
		virtual INT64	purchase_no()					=0;	//[8]주문번호
		virtual void	purchase_no(INT64 var)			=0;
		virtual INT32	item_no()						=0;	//[4]아이템번호
		virtual void	item_no(INT32 var)				=0;
		virtual PStr	item_name()						=0; //[?]아이템이름
		virtual void	item_name(PStr var)				=0;
		virtual PStr	item_code()						=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)				=0;
		virtual SHORT	order_quantity()				=0;	//[2]주문수량
		virtual void	order_quantity(SHORT var)		=0;
		virtual INT32	item_hour()						=0; //[4]아이템기간(시간)
		virtual void	item_hour(INT32 var)			=0;
		virtual SHORT	item_quantity()					=0;	//[2]아이템구성수량
		virtual void	item_quantity(SHORT var)		=0;
		virtual bool	is_include_bonus()				=0; //[1]보너스포함여부
		virtual void	is_include_bonus(bool var)		=0;
	};

	// Response Cart Item Structure
	class ICartItemInfo : public IObject
	{
	public:
		ICartItemInfo()				{}
		virtual ~ICartItemInfo()	{}

		//get,set
		virtual INT64	cart_no()					=0; //[8]카트번호
		virtual void	cart_no(INT64 var)			=0;
		virtual PStr	service_code()				=0; //[?]서비스코드
		virtual void	service_code(PStr var)		=0;
		virtual INT32	category_no()				=0; //[4]카테고리번호
		virtual void	category_no(INT32 var)		=0;
		virtual INT32	item_no()					=0; //[4]아이템번호
		virtual void	item_no(INT32 var)			=0;
		virtual PStr	item_name()					=0; //[?]아이템이름
		virtual void	item_name(PStr var)			=0;
		virtual PStr	item_code()					=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)			=0;
		virtual PStr	item_type()					=0; //[?]아이템타입
		virtual void	item_type(PStr var)			=0;
		virtual PStr	sale_type()					=0; //[?]판매타입
		virtual void	sale_type(PStr var)			=0;
		virtual PStr	item_sale_type()			=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)	=0;
		virtual bool	is_include_bonus()			=0; //[1]보너스포함여부
		virtual void	is_include_bonus(bool var)	=0;
		virtual INT32	item_cost()					=0; //[4]아이템원가
		virtual void	item_cost(INT32 var)		=0;
		virtual INT32	item_hour()					=0; //[4]기간제아이템일경우아이템유효기간
		virtual void	item_hour(INT32 var)		=0;
		virtual SHORT	item_quantity()				=0;	//[2]아이템구성수량
		virtual void	item_quantity(SHORT var)	=0;
		virtual INT32	total_quantity()			=0; //[4]총구성수량
		virtual void	total_quantity(INT32 var)	=0;
		virtual SHORT	reorder_term()				=0;	//[2]재주문가능시간(0 이면 무제한)
		virtual void	reorder_term(SHORT var)		=0;
		virtual BYTE	reorder_count()				=0;	//[1]재주문가능횟수(0 이면 무제한)
		virtual void	reorder_count(BYTE var)		=0;
		virtual INT32	user_no()					=0;	//[4]사용자번호
		virtual void	user_no(INT32 var)			=0;
		virtual PStr	user_id()					=0; //[?]사용자아이디
		virtual void	user_id(PStr var)			=0;
		virtual SHORT	order_quantity()			=0;	//[2]주문수량
		virtual void	order_quantity(SHORT var)	=0;
		virtual INT32	world_no()					=0;	//[4]월드번호
		virtual void	world_no(INT32 var)			=0;
		virtual PStr	world_key()					=0; //[?]월드키
		virtual void	world_key(PStr var)			=0;
		virtual INT32	chracter_no()				=0;	//[4]캐릭터번호
		virtual void	chracter_no(INT32 var)		=0;
		virtual PStr	chracter_id()				=0; //[?]캐릭터아이디
		virtual void	chracter_id(PStr var)		=0;
		virtual INT64	modify_datetime()			=0; //[8]수정일시
		virtual void	modify_datetime(INT64 var)	=0;
		virtual PStr	attribute0()				=0; //[?]확장속성
		virtual void	attribute0(PStr var)		=0;
		virtual PStr	attribute1()				=0; //[?]확장속성
		virtual void	attribute1(PStr var)		=0;
		virtual PStr	attribute2()				=0; //[?]확장속성
		virtual void	attribute2(PStr var)		=0;
		virtual PStr	attribute3()				=0; //[?]확장속성
		virtual void	attribute3(PStr var)		=0;
		virtual PStr	attribute4()				=0; //[?]확장속성
		virtual void	attribute4(PStr var)		=0;
		virtual PStr	description()				=0; //[?]설명
		virtual void	description(PStr var)		=0;
		virtual INT32	sale_price()				=0;	//[4]판매가
		virtual void	sale_price(INT32 var)		=0;
		virtual PStr	discount_type()				=0; //[?]할인유형
		virtual void	discount_type(PStr var)		=0;
		virtual INT32	discount_price()			=0;	//[4]할인금액
		virtual void	discount_price(INT32 var)	=0;
		virtual BYTE	discount_rate()				=0;	//[1]할인율(%)
		virtual void	discount_rate(BYTE var)		=0;
		virtual INT32	flat_price()				=0;	//[4]할인정가
		virtual void	flat_price(INT32 var)		=0;
	};
	
	// Request Register Item Structure : item 등록 
	class IRegisterItem : public IObject
	{
	public:
		IRegisterItem()				{}
		virtual ~IRegisterItem()		{}

		//get,set
		virtual INT32	category_no()					=0; //[4]카테고리번호
		virtual void	category_no(INT32 var)			=0;
		virtual INT32	item_no()						=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)				=0;
		virtual SHORT	purchase_quantity()				=0; //[2]구매수량
		virtual void	purchase_quantity(SHORT var)	=0;
		virtual PStr	attribute0()					=0; //[?]확장속성
		virtual void	attribute0(PStr var)			=0;
		virtual PStr	attribute1()					=0; //[?]확장속성
		virtual void	attribute1(PStr var)			=0;
		virtual PStr	attribute2()					=0; //[?]확장속성
		virtual void	attribute2(PStr var)			=0;
		virtual PStr	attribute3()					=0; //[?]확장속성
		virtual void	attribute3(PStr var)			=0;
		virtual PStr	attribute4()					=0; //[?]확장속성
		virtual void	attribute4(PStr var)			=0;
	};

	// Request Item Structure
	class ICartItem : public IObject
	{
	public:
		ICartItem()				{}
		virtual ~ICartItem()	{}

		//get,set
		virtual INT64	cart_no()					=0; //[8]카트번호
		virtual void	cart_no(INT64 var)			=0;
		virtual PStr	sale_type()					=0; //[?]판매유형
		virtual void	sale_type(PStr var)			=0;
		virtual PStr	discount_type()				=0; //[4]할인유형
		virtual void	discount_type(PStr var)		=0;
		virtual INT32	item_no()					=0; //[4]아이템번호
		virtual void	item_no(INT32 var)			=0;
		virtual PStr	item_sale_type()			=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)	=0;
		virtual PStr	item_type()					=0; //[?]아이템유형
		virtual void	item_type(PStr var)			=0;
		virtual INT32	purchase_price()			=0; //[4]판매가
		virtual void	purchase_price(INT32 var)	=0;
		virtual PStr	purchase_type()				=0; //[?]판매타입
		virtual void	purchase_type(PStr var)		=0;
	};

	// Request No
	class IRequestNo : public IObject
	{
	public:
		IRequestNo()			{}
		virtual ~IRequestNo()	{}

		//get,set
		virtual INT64	no()			=0; //[8]카트/위시리스트 번호
		virtual void	no(INT64 var)	=0;
	};

	// Response Wish Item
	class IWishItemInfo : public IObject
	{
	public:
		IWishItemInfo()				{}
		virtual ~IWishItemInfo()	{}

		//get,set
		virtual INT64	wish_no()					=0; //[8]Wish 번호
		virtual void	wish_no(INT64 var)			=0;
		virtual PStr	service_code()				=0; //[?]서비스코드
		virtual void	service_code(PStr var)		=0;
		virtual INT32	category_no()				=0; //[4]카테고리번호
		virtual void	category_no(INT32 var)		=0;
		virtual INT32	item_no()					=0; //[4]아이템번호
		virtual void	item_no(INT32 var)			=0;
		virtual PStr	item_name()					=0; //[?]아이템이름
		virtual void	item_name(PStr var)			=0;
		virtual PStr	item_code()					=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)			=0;
		virtual PStr	item_type()					=0; //[?]아이템타입
		virtual void	item_type(PStr var)			=0;
		virtual PStr	sale_type()					=0; //[?]판매타입
		virtual void	sale_type(PStr var)			=0;
		virtual PStr	item_sale_type()			=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)	=0;
		virtual INT32	item_cost()					=0; //[4]아이템원가
		virtual void	item_cost(INT32 var)		=0;
		virtual INT32	item_hour()					=0; //[4]기간제아이템일경우아이템유효기간
		virtual void	item_hour(INT32 var)		=0;
		virtual SHORT	item_quantity()				=0;	//[2]아이템구성수량
		virtual void	item_quantity(SHORT var)	=0;
		virtual INT32	total_quantity()			=0; //[4]총구성수량
		virtual void	total_quantity(INT32 var)	=0;
		virtual SHORT	reorder_term()				=0;	//[2]재주문가능시간(0 이면 무제한)
		virtual void	reorder_term(SHORT var)		=0;
		virtual BYTE	reorder_count()				=0;	//[1]재주문가능횟수(0 이면 무제한)
		virtual void	reorder_count(BYTE var)		=0;
		virtual INT32	user_no()					=0;	//[4]사용자번호
		virtual void	user_no(INT32 var)			=0;
		virtual PStr	user_id()					=0; //[?]사용자아이디
		virtual void	user_id(PStr var)			=0;
		virtual INT32	world_no()					=0;	//[4]월드번호
		virtual void	world_no(INT32 var)			=0;
		virtual PStr	world_key()					=0; //[?]월드키
		virtual void	world_key(PStr var)			=0;
		virtual INT32	chracter_no()				=0;	//[4]캐릭터번호
		virtual void	chracter_no(INT32 var)		=0;
		virtual PStr	chracter_id()				=0; //[?]캐릭터아이디
		virtual void	chracter_id(PStr var)		=0;
		virtual INT64	modify_datetime()			=0; //[8]수정일시
		virtual void	modify_datetime(INT64 var)	=0;
		virtual PStr	description()				=0; //[?]설명
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
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual PStr	purchase_guid()						=0; //[?]주문상태 값
		virtual void	purchase_guid(PStr var)				=0;
		virtual INT32	user_no()							=0; //[4]사용자번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자ID
		virtual void	user_id(PStr var)					=0;
		virtual PStr	service_code()						=0; //[?]서비스코드
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]월드번호
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]월드키
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터 번호
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터 이름
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]아이템이름
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]아이템유형
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)			=0;
		virtual bool	is_include_bonus()					=0; //[1]보너스상품보유여부
		virtual void	is_include_bonus(bool var)			=0;
		virtual bool	is_gift()							=0; //[1]선물여부
		virtual void	is_gift(bool var)					=0;
		virtual SHORT	order_quantity()					=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)			=0;
		virtual INT64	first_receive_datetime()			=0; //[8]처음수령시간 (C#의 Tick)
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]최종수령시간 (C#의 Tick)
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT32	sender_user_no()					=0; //[4]보낸사람번호
		virtual void	sender_user_no(INT32 var)			=0;
		virtual PStr	sender_user_id()					=0; //[?]보낸사람아이디
		virtual void	sender_user_id(PStr var)			=0;
		virtual INT32	sender_world_no()					=0; //[4]보낸월드번호
		virtual void	sender_world_no(INT32 var)			=0;
		virtual PStr	sender_world_key()					=0; //[?]보낸월드키
		virtual void	sender_world_key(PStr var)			=0;
		virtual INT32	sender_character_no()				=0; //[4]보낸캐릭터번호
		virtual void	sender_character_no(INT32 var)		=0;
		virtual PStr	sender_character_id()				=0; //[?]보낸캐릭터 Id
		virtual void	sender_character_id(PStr var)		=0;
		virtual PStr	send_message()						=0; //[?]메시지
		virtual void	send_message(PStr var)				=0;
		virtual SHORT	inventory_keep_days()				=0; //[2]인벤토리보유기간
		virtual void	inventory_keep_days(SHORT var)		=0;
		virtual SHORT	item_quantity()						=0; //[2]개별수량
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]사용기간
		virtual void	item_hour(INT32 var)				=0;
		virtual INT64	register_datetime()					=0; //[8]등록시간 (C#의 Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]확장속성
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]확장속성
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]확장속성
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]확장속성
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]확장속성
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]상품설명
		virtual void	description(PStr var)				=0;
	};

	// Cash Inventory Package Items Structure
	class IPackageItem : public IObject
	{
	public:
		IPackageItem()			{}
		virtual ~IPackageItem()	{}

		//get,set
		virtual INT64	package_inventory_no()				=0; //[8] 패키지인벤토리번호
		virtual void	package_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]사용자번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자ID
		virtual void	user_id(PStr var)					=0;
		virtual PStr	service_code()						=0; //[?]서비스코드
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]월드번호
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]월드키
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터 번호
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터 이름
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]아이템이름
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]아이템유형
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]개별수량
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]사용기간
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]멤버수량
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]인벤토리보관일수
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]처음수량시간(C#의 Tick)
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]최종수령시간(C#의 Tick)
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]등록시간 (C#의 Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]확장속성
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]확장속성
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]확장속성
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]확장속성
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]확장속성
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]상품설명
		virtual void	description(PStr var)				=0;
	};

	// Cash Inventory Lottery Items Structure
	class ILotteryItem : public IObject
	{
	public:
		ILotteryItem()			{}
		virtual ~ILotteryItem()	{}

		//get,set
		virtual INT64	lottery_inventory_no()				=0; //[8]복권인벤토리벤토리번호
		virtual void	lottery_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]주문인벤토리번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]사용자번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자ID
		virtual void	user_id(PStr var)					=0;
		virtual PStr	service_code()						=0; //[?]서비스코드
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]월드번호
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]월드키
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터 번호
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터 이름
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]아이템이름
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]아이템유형
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]개별수량
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]사용기간
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]멤버수량
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]인벤토리보관일수
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]처음수량시간(C#의 Tick)
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]최종수령시간(C#의 Tick)
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]등록시간 (C#의 Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]확장속성
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]확장속성
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]확장속성
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]확장속성
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]확장속성
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]상품설명
		virtual void	description(PStr var)				=0;
	};
	
	// Cash Inventory Bonus Items Structure
	class IBonusItem : public IObject
	{
	public:
		IBonusItem()			{}
		virtual ~IBonusItem()	{}

		//get,set
		virtual INT64	bonus_inventory_no()				=0; //[8]보너스인벤토리번호
		virtual void	bonus_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]주문인벤토리번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]사용자번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자ID
		virtual void	user_id(PStr var)					=0;
		virtual PStr	service_code()						=0; //[?]서비스코드
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]월드번호
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]월드키
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터 번호
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터 이름
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]아이템이름
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]아이템유형
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]개별수량
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]사용기간
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]멤버수량
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]남은수량
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]인벤토리보관일수
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]처음수량시간(C#의 Tick)
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]최종수령시간(C#의 Tick)
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]등록시간 (C#의 Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]확장속성
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]확장속성
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]확장속성
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]확장속성
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]확장속성
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]상품설명
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
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual PStr	purchase_guid()						=0; //[?]주문상태 값
		virtual void	purchase_guid(PStr var)				=0;
		virtual INT32	user_no()							=0; //[4]사용자번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자ID
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0; //[4]계정 번호
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]계정 ID
		virtual void	account_id(PStr var)				=0;
		virtual PStr	service_code()						=0; //[?]서비스코드
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]월드번호
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]월드키
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터 번호
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터 이름
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]아이템이름
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]아이템유형
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)			=0;
		virtual bool	is_include_bonus()					=0; //[1]보너스상품보유여부
		virtual void	is_include_bonus(bool var)			=0;
		virtual bool	is_gift()							=0; //[1]선물여부
		virtual void	is_gift(bool var)					=0;
		virtual SHORT	order_quantity()					=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]남은수량 : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	remain_quantity(SHORT var)			=0;
		virtual INT64	first_receive_datetime()			=0; //[8]처음수령시간 (C#의 Tick) : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]최종수령시간 (C#의 Tick) : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT32	sender_user_no()					=0; //[4]보낸사람번호
		virtual void	sender_user_no(INT32 var)			=0;
		virtual PStr	sender_user_id()					=0; //[?]보낸사람아이디
		virtual void	sender_user_id(PStr var)			=0;
		virtual INT32	sender_account_no()					=0; //[4]보낸 계정 번호
		virtual void	sender_account_no(INT32 var)		=0;
		virtual PStr	sender_account_id()					=0; //[?]보낸 계정 ID
		virtual void	sender_account_id(PStr var)			=0;
		virtual INT32	sender_world_no()					=0; //[4]보낸월드번호
		virtual void	sender_world_no(INT32 var)			=0;
		virtual PStr	sender_world_key()					=0; //[?]보낸월드키
		virtual void	sender_world_key(PStr var)			=0;
		virtual INT32	sender_character_no()				=0; //[4]보낸캐릭터번호
		virtual void	sender_character_no(INT32 var)		=0;
		virtual PStr	sender_character_id()				=0; //[?]보낸캐릭터 Id
		virtual void	sender_character_id(PStr var)		=0;
		virtual PStr	send_message()						=0; //[?]메시지
		virtual void	send_message(PStr var)				=0;
		virtual SHORT	inventory_keep_days()				=0; //[2]인벤토리보유기간
		virtual void	inventory_keep_days(SHORT var)		=0;
		virtual SHORT	item_quantity()						=0; //[2]개별수량
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]사용기간
		virtual void	item_hour(INT32 var)				=0;
		virtual INT64	register_datetime()					=0; //[8]등록시간 (C#의 Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]확장속성
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]확장속성
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]확장속성
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]확장속성
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]확장속성
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]상품설명
		virtual void	description(PStr var)				=0;
	};

	
	// Cash Inventory Package Items Structure by Bind Attribute
	class IPackageItemByBindAttribute : public IObject
	{
	public:
		IPackageItemByBindAttribute()			{}
		virtual ~IPackageItemByBindAttribute()	{}

		//get,set
		virtual INT64	package_inventory_no()				=0; //[8] 패키지인벤토리번호
		virtual void	package_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]주문번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]사용자번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자ID
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0; //[4]계정 번호
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]계정 ID
		virtual void	account_id(PStr var)				=0;
		virtual PStr	service_code()						=0; //[?]서비스코드
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]월드번호
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]월드키
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터 번호
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터 이름
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]아이템이름
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]아이템유형
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]개별수량
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]사용기간
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]멤버수량
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]남은수량 : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]인벤토리보관일수
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]처음수량시간(C#의 Tick) : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]최종수령시간(C#의 Tick) : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]등록시간 (C#의 Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]확장속성
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]확장속성
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]확장속성
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]확장속성
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]확장속성
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]상품설명
		virtual void	description(PStr var)				=0;
	};

	// Cash Inventory Lottery Items Structure by Bind Attribute
	class ILotteryItemByBindAttribute : public IObject
	{
	public:
		ILotteryItemByBindAttribute()			{}
		virtual ~ILotteryItemByBindAttribute()	{}

		//get,set
		virtual INT64	lottery_inventory_no()				=0; //[8]복권인벤토리벤토리번호
		virtual void	lottery_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]주문인벤토리번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]사용자번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자ID
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0; //[4]계정 번호
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]계정 ID
		virtual void	account_id(PStr var)				=0;
		virtual PStr	service_code()						=0; //[?]서비스코드
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]월드번호
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]월드키
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터 번호
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터 이름
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]아이템이름
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]아이템유형
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]개별수량
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]사용기간
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]멤버수량
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]남은수량 : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]인벤토리보관일수
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]처음수량시간(C#의 Tick) : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]최종수령시간(C#의 Tick) : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]등록시간 (C#의 Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]확장속성
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]확장속성
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]확장속성
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]확장속성
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]확장속성
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]상품설명
		virtual void	description(PStr var)				=0;
	};
	
	// Cash Inventory Bonus Items Structure by Bind Attribute
	class IBonusItemByBindAttribute : public IObject
	{
	public:
		IBonusItemByBindAttribute()				{}
		virtual ~IBonusItemByBindAttribute()	{}

		//get,set
		virtual INT64	bonus_inventory_no()				=0; //[8]보너스인벤토리번호
		virtual void	bonus_inventory_no(INT64 var)		=0;
		virtual INT64	purchase_no()						=0; //[8]주문인벤토리번호
		virtual void	purchase_no(INT64 var)				=0;
		virtual INT32	user_no()							=0; //[4]사용자번호
		virtual void	user_no(INT32 var)					=0;
		virtual PStr	user_id()							=0; //[?]사용자ID
		virtual void	user_id(PStr var)					=0;
		virtual INT32	account_no()						=0; //[4]계정 번호
		virtual void	account_no(INT32 var)				=0;
		virtual PStr	account_id()						=0; //[?]계정 ID
		virtual void	account_id(PStr var)				=0;
		virtual PStr	service_code()						=0; //[?]서비스코드
		virtual void	service_code(PStr var)				=0;
		virtual INT32	world_no()							=0; //[4]월드번호
		virtual void	world_no(INT32 var)					=0;
		virtual PStr	world_key()							=0; //[?]월드키
		virtual void	world_key(PStr var)					=0;
		virtual INT32	character_no()						=0; //[4]캐릭터 번호
		virtual void	character_no(INT32 var)				=0;
		virtual PStr	character_id()						=0; //[?]캐릭터 이름
		virtual void	character_id(PStr var)				=0;
		virtual INT32	item_no()							=0; //[4]아이템관리번호
		virtual void	item_no(INT32 var)					=0;
		virtual PStr	item_name()							=0; //[?]아이템이름
		virtual void	item_name(PStr var)					=0;
		virtual PStr	item_code()							=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)					=0;
		virtual PStr	item_type()							=0; //[?]아이템유형
		virtual void	item_type(PStr var)					=0;
		virtual PStr	item_sale_type()					=0; //[?]아이템판매타입
		virtual void	item_sale_type(PStr var)			=0;
		virtual SHORT	item_quantity()						=0; //[2]개별수량
		virtual void	item_quantity(SHORT var)			=0;
		virtual INT32	item_hour()							=0; //[4]사용기간
		virtual void	item_hour(INT32 var)				=0;
		virtual SHORT	member_quantity()					=0; //[2]멤버수량
		virtual void	member_quantity(SHORT var)			=0;
		virtual SHORT	order_quantity()					=0; //[2]주문수량
		virtual void	order_quantity(SHORT var)			=0;
		virtual SHORT	remain_quantity()					=0; //[2]남은수량 : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	remain_quantity(SHORT var)			=0;
		virtual SHORT	inventory_keey_days()				=0; //[2]인벤토리보관일수
		virtual void	inventory_keey_days(SHORT var)		=0;
		virtual INT64	first_receive_datetime()			=0; //[8]처음수량시간(C#의 Tick) : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	first_receive_datetime(INT64 var)	=0;
		virtual INT64	last_receive_datetime()				=0; //[8]최종수령시간(C#의 Tick) : Advanced Billing - Cash Inventory 의 Step 12. 에서는 사용 안 됨
		virtual void	last_receive_datetime(INT64 var)	=0;
		virtual INT64	register_datetime()					=0; //[8]등록시간 (C#의 Tick)
		virtual void	register_datetime(INT64 var)		=0;
		virtual	PStr	attribute0()						=0; //[?]확장속성
		virtual void	attribute0(PStr var)				=0;
		virtual	PStr	attribute1()						=0; //[?]확장속성
		virtual void	attribute1(PStr var)				=0;
		virtual	PStr	attribute2()						=0; //[?]확장속성
		virtual void	attribute2(PStr var)				=0;
		virtual	PStr	attribute3()						=0; //[?]확장속성
		virtual void	attribute3(PStr var)				=0;
		virtual	PStr	attribute4()						=0; //[?]확장속성
		virtual void	attribute4(PStr var)				=0;
		virtual	PStr	description()						=0; //[?]상품설명
		virtual void	description(PStr var)				=0;
	};

	// 
	class IPickupStandbyCashInventoryItem : public IObject
	{
	public:
		IPickupStandbyCashInventoryItem()			{}
		virtual ~IPickupStandbyCashInventoryItem()	{}

		//get,set
		virtual BYTE	item_expand_flag()			=0; //[1]Cash Inventory Item Expand Flags (fcs_constant.h의 "Table 11 Inquiry Cash Inventory Expand Flags" 참조)
		virtual void	item_expand_flag(BYTE var)	=0;
		virtual INT32	item_no()					=0;	//[4]아이템코드
		virtual void	item_no(INT32 var)			=0;
		virtual PStr	item_code()					=0; //[?]게임아이템관리코드
		virtual void	item_code(PStr var)			=0;
		virtual PStr	item_type()					=0; //[?]아이템유형
		virtual void	item_type(PStr var)			=0;
		virtual SHORT	item_quantity()				=0; //[2]개별수량
		virtual void	item_quantity(SHORT var)	=0;
		virtual INT32	item_hour()					=0; //[4]사용기간
		virtual void	item_hour(INT32 var)		=0;
		virtual	PStr	attribute0()				=0; //[?]확장속성
		virtual void	attribute0(PStr var)		=0;
		virtual	PStr	attribute1()				=0; //[?]확장속성
		virtual void	attribute1(PStr var)		=0;
		virtual	PStr	attribute2()				=0; //[?]확장속성
		virtual void	attribute2(PStr var)		=0;
		virtual	PStr	attribute3()				=0; //[?]확장속성
		virtual void	attribute3(PStr var)		=0;

	};

	// Use Storage STItemProperty Structure
	class ISTItemProperty : public IObject
	{
	public:
		ISTItemProperty()			{}
		virtual ~ISTItemProperty()	{}

		//get,set
		virtual INT32	property_seq()			=0; //[4]속성 번호
		virtual void	property_seq(INT32 var)	=0;
		virtual INT32	value()					=0; //[4]속성 값
		virtual void	value(INT32 var)		=0;
	};

	// Jewel Balance Item Structure
	class IJewelBalanceItem : public IObject
	{
	public :
		IJewelBalanceItem()			{}
		virtual ~IJewelBalanceItem()	{}

		virtual	INT32	cash_type()				=0; //[?]화폐 종류종류  (Table 18 Cash Type)
		virtual void	cash_type(INT32 var)	=0;
		virtual INT64	coin()					=0; //[8]잔액
		virtual void	coin(INT64 var)			=0;
	};

	// WShop
	class IPStrA : public IObject
	{
	public :
		IPStrA()			{}
		virtual ~IPStrA()	{}

		virtual PStr	value()							    =0; //[?]문자열
		virtual void	value(PStr var)						=0;
	};

	class IWShopRequestPurchaseItem : public IObject
	{
	public:
		IWShopRequestPurchaseItem()				{}
		virtual ~IWShopRequestPurchaseItem()	{}

	public:
		virtual INT32	item_sale_no() =0; //[4] 아이템 판매 번호
		virtual void	item_sale_no(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT32	purchase_price() =0; //[4] 구매 금액 (할인룰 있는경우는 할인 적용된 금액)
		virtual void	purchase_price(INT32 var) = 0;
		virtual SHORT	order_quantity() =0; //[2] 주문수량
		virtual void	order_quantity(SHORT var) = 0;
		virtual PStr	attribute0() =0; //[?] 속성 (클라라의 Property0) : optional
		virtual void	attribute0(PStr var) = 0;
		virtual PStr	attribute1() =0; //[?] 속성 (클라라의 Property1) : optional
		virtual void	attribute1(PStr var) = 0;
		virtual PStr	attribute2() =0; //[?] 속성 (클라라의 Property2) : optional
		virtual void	attribute2(PStr var) = 0;
		virtual PStr	attribute3() =0; //[?] 속성 (클라라의 Property3) : optional
		virtual void	attribute3(PStr var) = 0;
		virtual PStr	attribute4() =0; //[?] 속성 (클라라의 Property4) : optional
		virtual void	attribute4(PStr var) = 0;
		virtual PStr	description() =0; //[?] 설명 : optional
		virtual void	description(PStr var) = 0;
	};

	class IWShopResponseApproval : public IObject
	{
	public :
		IWShopResponseApproval()			{}
		virtual ~IWShopResponseApproval()	{}

		virtual INT32	item_sale_no() =0; //[4] 아이템 판매 번호
		virtual void	item_sale_no(INT32 var) = 0;
		virtual PStr	order_id() =0; //[?] 주문번호
		virtual void	order_id(PStr var) = 0;
		virtual INT64	purchase_no() =0; //[8] 선물 시 발급된 구매번호
		virtual void	purchase_no(INT64 var) = 0;
		virtual PStr	item_code() =0; //[?] 아이템 코드
		virtual void	item_code(PStr var) = 0;
		virtual INT32	item_minute() =0; //[4] 아이템 유효 사용 기간(분)
		virtual void	item_minute(INT32 var) = 0;
		virtual SHORT	order_quantity() =0; //[2] 주문수량
		virtual void	order_quantity(SHORT var) = 0;
		virtual PStr	attribute0() =0; //[?] 속성 (클라라의 Property0)
		virtual void	attribute0(PStr var) = 0;
		virtual PStr	attribute1() =0; //[?] 속성 (클라라의 Property1)
		virtual void	attribute1(PStr var) = 0;
		virtual PStr	attribute2() =0; //[?] 속성 (클라라의 Property2)
		virtual void	attribute2(PStr var) = 0;
		virtual PStr	attribute3() =0; //[?] 속성 (클라라의 Property3)
		virtual void	attribute3(PStr var) = 0;
		virtual PStr	attribute4() =0; //[?] 속성 (클라라의 Property4)
		virtual void	attribute4(PStr var) = 0;
	};

	class IWShopRequestOrderId : public IObject
	{
	public :
		IWShopRequestOrderId()			{}
		virtual ~IWShopRequestOrderId()	{}

		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문 번호
		virtual void	order_id(PStr var) = 0;
	};

	class IWShopInventoryItem : public IObject
	{
	public :
		IWShopInventoryItem()			{}
		virtual ~IWShopInventoryItem()	{}

		virtual PStr	purchase_order_id() =0; //[?] 이 아이템 구매 시 사용되었던 게임 측 주문 번호
		virtual void	purchase_order_id(PStr var) = 0;
		virtual INT64	purchase_no() =0; //[8] 아이템의 구매 결과로 생성된 구매 번호
		virtual void	purchase_no(INT64 var) = 0;
		virtual INT32	item_no() =0; //[4] 아이템의 번호
		virtual void	item_no(INT32 var) = 0;
		virtual PStr	item_code() =0; //[?] 게임에서 인지하고 있는 아이템 코드 값
		virtual void	item_code(PStr var) = 0;
		virtual INT32	item_minute() =0; //[4] 아이템의 유효 사용 기간 (분)
		virtual void	item_minute(INT32 var) = 0;
		virtual SHORT	item_quantity() =0; //[2] 아이템 수량
		virtual void	item_quantity(SHORT var) = 0;
		virtual INT64	register_date_time() =0; //[8] 이 아이템이 인벤토리에 등록된 일시
		virtual void	register_date_time(INT64 var) = 0;
		virtual INT32	inventory_keep_days() =0; //[4] 인벤토리 남은 보관 기간 (일)
		virtual void	inventory_keep_days(INT32 var) = 0;
		virtual bool	is_gift() =0; //[1] (구매 보관함) 선물 여부
		virtual void	is_gift(bool var) = 0;
		virtual INT32	sender_user_no() =0; //[4] (Is Gift가 참일 때) 선물 보낸 사용자 번호
		virtual void	sender_user_no(INT32 var) = 0;
		virtual PStr	sender_user_id() =0; //[?] (Is Gift가 참일 때) 선물 보낸 사용자 아이디
		virtual void	sender_user_id(PStr var) = 0;
		virtual INT32	sender_account_no() =0; //[4] (Is Gift가 참일 때) 선물 보낸 계정 번호
		virtual void	sender_account_no(INT32 var) = 0;
		virtual PStr	sender_account_id() =0; //[?] (Is Gift가 참일 때) 선물 보낸 계정 아이디
		virtual void	sender_account_id(PStr var) = 0;
		virtual PStr	sender_world_key() =0; //[?] (Is Gift가 참일 때)  선물 보낸 서버 키
		virtual void	sender_world_key(PStr var) = 0;
		virtual INT64	sender_character_no() =0; //[8] (Is Gift가 참일 때)  선물 보낸 캐릭터 번호
		virtual void	sender_character_no(INT64 var) = 0;
		virtual PStr	sender_character_id() =0; //[?] (Is Gift가 참일 때) 선물 보낸 캐릭터 명
		virtual void	sender_character_id(PStr var) = 0;
		virtual PStr	send_message() =0; //[?] (Is Gift가 참일 때) 선물 메시지
		virtual void	send_message(PStr var) = 0;
	};

	class IWShopPickUpItem : public IObject
	{
	public :
		IWShopPickUpItem()			{}
		virtual ~IWShopPickUpItem()	{}

		virtual PStr	order_id() =0; //[?] 수령 동작에 대한 게임 측 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT64	purchase_no() =0; //[8] 이 아이템에 대한 구매 번호
		virtual void	purchase_no(INT64 var) = 0;
		virtual PStr	item_code() =0; //[?] 아이템 코드
		virtual void	item_code(PStr var) = 0;
		virtual INT32	item_minute() =0; //[4] 아이템 기간 (분)
		virtual void	item_minute(INT32 var) = 0;
		virtual SHORT	item_quantity() =0; //[2] 수령 아이템 수량
		virtual void	item_quantity(SHORT var) = 0;
	};

	class IWShopResponseOrderStatus : public IObject
	{
	public :
		IWShopResponseOrderStatus()				{}
		virtual ~IWShopResponseOrderStatus()	{}

		virtual PStr	order_id() =0; //[?] 게임에서 생성한 유니크한 주문 번호
		virtual void	order_id(PStr var) = 0;
		virtual INT32	order_status() =0; //[4] 현재 주문 상태 (Table 25 Order Status Type)
		virtual void	order_status(INT32 var) = 0;
	};

//## SUB DTO : END
//#################################################################################################

} // namespace

#endif