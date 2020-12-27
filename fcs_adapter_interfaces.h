#ifndef FCSADAPTER_INTERFACE_FCSADAPTER_INTERFACES_H_
#define FCSADAPTER_INTERFACE_FCSADAPTER_INTERFACES_H_

#include "fcs_adapter_interfaces_dto.h"


namespace fcsa {

	// forward declaration
	class IAuth;
	class IBasicBilling;
	class IWShopBilling;
	class IWShopInventory;
	class IJewel;
	class ICashInventory;
	class IInquiryOData;
	class ICartAndWishItems;
	class IOrder;
	class ICoupon;

	class IAsyncReceiverAuth;
	class IAsyncReceiverBasicBilling;
	class IAsyncReceiverWShopBilling;
	class IAsyncReceiverWShopInventory;
	class IAsyncReceiverJewel;
	class IAsyncReceiverCashInventory;
	class IAsyncReceiverStatus;			// Shop ���� ������ ������ ������ ���º����� �˸��ް��� �� ���, ����Ѵ�.
	class IAsyncReceiverInquiryOData;
	class IAsyncReceiverCartAndWishItems;
	class IAsyncReceiverOrder;
	class IAsyncReceiverCoupon;
	class IManager : public IObject
	{
	public:
		IManager() {}
		virtual ~IManager() {}

	public:
		virtual INT32 getWorldNo() = 0;

		// FCSAdapter.dll �ʱ�ȭ �Ϸ� ����(blocking mode)
		//		�ִ� ��� �ð� 30��
		//		�������� ��� 1msec ~ 10msec �ȿ� �ʱ�ȭ �Ϸ�
		//		FCS ������ connection �� ���� ���ϸ� �ִ� ��� �ð����� ��� �� false ����
		virtual bool isInitializedWait() =0;

		// FCSAdapter.dll �ʱ�ȭ �Ϸ� ����(non-blocking mode)
		virtual bool isInitialized() =0;	

		// OData ��ȸ �� ���� �� ������ ���� ���
		virtual void setItemVersion(INT64 version) = 0;

		/*
		����� ���� �ν��Ͻ� ����.			
			thread ���� �ϳ��� �������̽��� �����Ͽ� ����ؾ� �մϴ�.
			createInstance...() �� ������ ��ü�� ����� ������ �ݵ�� release()�� �ڿ����� �ؾ��մϴ�.
		*/
		virtual IAuth*					createInstanceAuth()				=0;	// Authentication & Authorization
		virtual IBasicBilling*			createInstanceBasicBilling()		=0;	// Basic Billing
		virtual IWShopBilling*			createInstanceWShopBilling()		=0;	// WShop Billing
		virtual IWShopInventory*		createInstanceWShopInventory()		=0;	// WShop Inventory
		virtual IJewel*					createInstanceJewel()				=0;	// Jewel
		virtual ICashInventory*			createInstanceCashInventory()		=0;	// Advanced Billing - Cash Inventory
		virtual IInquiryOData*			createInstanceInquiryOData()		=0;	// Advanced Billing - Inquiry OData
		virtual ICartAndWishItems*		createInstanceCartAndWishItems()	=0;	// Advanced Billing - Cart & Wish Items
		virtual IOrder*					createInstanceOrder()				=0;	// Advanced Billing - Order
		virtual ICoupon*				createInstanceCoupon()				=0;	// Coupon

		/*
			�񵿱�(Async) ���� ���� ������ ������ ��ü ����
			FCSAdapter.dll �ʱ�ȭ�ÿ� receiver ��ü�� �����ϰ� 
			FCSAdapter.dll ����� ���� �Ŀ� receiver ��ü�� �Ҹ��Ű�ʽÿ�.
			reset�� ���� lock�� ���� �ʱ� ������ runtime �� ������ ������ �� �ֽ��ϴ�.
			
			���1. �� �������̽� �����Ͽ� Receiver�� ����ϸ� �񵿱� ȣ��� ������ �ش� ��ü���� �������ش�.
			���2. callback response�� �׻� AsyncReceiver �� ���� �޴´�.
		*/
		virtual bool resetAsyncReceiverAuth(IAsyncReceiverAuth* receiver = NULL)							=0; // AsyncReceiver : Authentication & Authorization
		virtual bool resetAsyncReceiverBasicBilling(IAsyncReceiverBasicBilling* receiver = NULL)			=0;	// AsyncReceiver : Basic Billing
		virtual bool resetAsyncReceiverWShopBilling(IAsyncReceiverWShopBilling* receiver = NULL)			=0;	// AsyncReceiver : WShop Billing
		virtual bool resetAsyncReceiverWShopInventory(IAsyncReceiverWShopInventory* receiver = NULL)		=0;	// AsyncReceiver : WShop Inventory
		virtual bool resetAsyncReceiverJewel(IAsyncReceiverJewel* receiver = NULL)							=0;	// AsyncReceiver : Jewel
		virtual bool resetAsyncReceiverCashInventory(IAsyncReceiverCashInventory* receiver = NULL)			=0;	// AsyncReceiver : Advanced Billing - Cash Inventory
		virtual bool resetAsyncReceiverStatus(IAsyncReceiverStatus* receiver = NULL)						=0;	// AsyncReceiver : Status
		virtual bool resetAsyncReceiverInquiryOData(IAsyncReceiverInquiryOData* receiver = NULL)			=0;	// AsyncReceiver : Advanced Billing - Inquiry OData
		virtual bool resetAsyncReceiverCartAndWishItems(IAsyncReceiverCartAndWishItems* receiver = NULL)	=0;	// AsyncReceiver : Advanced Billing - Cart & Wish Items
		virtual bool resetAsyncReceiverOrder(IAsyncReceiverOrder* receiver = NULL)							=0;	// AsyncReceiver : Advanced Billing - Order
		virtual bool resetAsyncReceiverCoupon(IAsyncReceiverCoupon* receiver = NULL)						=0;	// AsyncReceiver : Coupon
	};


///////////////////////////////////////////////////////////////////////////////////////////////////
// Communicate Interface

	// Authentication & Authorization : thread unsafe
	class IAuth : public IObject
	{
	public:
		IAuth(){}
		virtual ~IAuth(){}

	public:
		// Authentication & Authorization Step 1: Game Login : ���� �α���
		virtual IRequestGameLogin* createRequestGameLogin()		= 0;
		virtual IResponseGameLogin* createResponseGameLogin()	= 0;
		virtual bool sendSync(IRequestGameLogin* req, IResponseGameLogin* res)		= 0;
		virtual bool sendAsync(IRequestGameLogin* req)	= 0;

		// Authentication & Authorization Step 2: Game Logout : ���� �α׾ƿ�
		virtual IRequestGameLogout* createRequestGameLogout()		= 0;
		virtual IResponseGameLogout* createResponseGameLogout()		= 0;
		virtual bool sendSync(IRequestGameLogout* req, IResponseGameLogout* res)	= 0;
		virtual bool sendAsync(IRequestGameLogout* req)	= 0;

		// Authentication & Authorization Step 3: Premium Service Expired Callback : �����̾� ���� �Ⱓ ����
		//	callback �̹Ƿ� ���� ����
		
		// Authentication & Authorization Step 4: Force User Logout Callback : ���� �α׾ƿ�
		//	callback �̹Ƿ� ���� ����

		// Authentication & Authorization Step 5: Request Authentication Key : ����Ű ��û
		virtual IRequestAuthenticationKey* createRequestAuthenticationKey()		= 0;
		virtual IResponseAuthenticationKey* createResponseAuthenticationKey()	= 0;
		virtual bool sendSync(IRequestAuthenticationKey* req, IResponseAuthenticationKey* res)		= 0;
		virtual bool sendAsync(IRequestAuthenticationKey* req)	= 0;

		// Authentication & Authorization Step 6: Validate Authentication Key : ����Ű ��ȿ�� �˻�
		virtual IRequestValidateAuthenticationKey* createRequestValidateAuthenticationKey()		= 0;
		virtual IResponseValidateAuthenticationKey* createResponseValidateAuthenticationKey()	= 0;
		virtual bool sendSync(IRequestValidateAuthenticationKey* req, IResponseValidateAuthenticationKey* res)	= 0;
		virtual bool sendAsync(IRequestValidateAuthenticationKey* req)			= 0;

		// Authentication & Authorization Step 7: Validate Authentication Key with Extension : ����Ű ��ȿ�� �˻�
		virtual IRequestValidateAuthenticationKeyWithExtension* createRequestValidateAuthenticationKeyWithExtension()	= 0;
		virtual IResponseValidateAuthenticationKeyWithExtension* createResponseValidateAuthenticationKeyWithExtension()	= 0;
		virtual bool sendSync(IRequestValidateAuthenticationKeyWithExtension* req, IResponseValidateAuthenticationKeyWithExtension* res) = 0;
		virtual bool sendAsync(IRequestValidateAuthenticationKeyWithExtension* req)= 0;

		// Authentication & Authorization Step 8: Validate Authentication Key for Publisher : ����Ű ��ȿ�� �˻�
		virtual IRequestValidateAuthenticationKeyForPublisher* createRequestValidateAuthenticationKeyForPublisher() = 0;
		virtual IResponseValidateAuthenticationKeyForPublisher* createResponseValidateAuthenticationKeyForPublisher() = 0;
		virtual bool sendSync(IRequestValidateAuthenticationKeyForPublisher* req, IResponseValidateAuthenticationKeyForPublisher* res) = 0;
		virtual bool sendAsync(IRequestValidateAuthenticationKeyForPublisher* req) = 0;

		// Authentication & Authorization Step 9: Validate Authentication Key with Parent Safe : �θ� �Ƚ� ���� ����Ű ��ȿ�� �˻�
		virtual IRequestValidateAuthenticationKeyWithParentSafe* createRequestValidateAuthenticationKeyWithParentSafe() = 0;
		virtual IResponseValidateAuthenticationKeyWithParentSafe* createResponseValidateAuthenticationKeyWithParentSafe() = 0;
		virtual bool sendSync(IRequestValidateAuthenticationKeyWithParentSafe* req, IResponseValidateAuthenticationKeyWithParentSafe* res) = 0;
		virtual bool sendAsync(IRequestValidateAuthenticationKeyWithParentSafe* req) = 0;

		// Authentication & Authorization Step 10: Validate Authentication Key for R2 : ���� R2�� ����Ű ��ȿ�� �˻�
		virtual IRequestValidateAuthenticationKeyForR2* createRequestValidateAuthenticationKeyForR2() = 0;
		virtual IResponseValidateAuthenticationKeyForR2* createResponseValidateAuthenticationKeyForR2() = 0;
		virtual bool sendSync(IRequestValidateAuthenticationKeyForR2* req, IResponseValidateAuthenticationKeyForR2* res) = 0;
		virtual bool sendAsync(IRequestValidateAuthenticationKeyForR2* req) = 0;

		// Authentication & Authorization Step 11: Validate Authentication Key with User Info : ����Ű ��ȿ�� �˻� (���� ���� Ȯ��)
		virtual IRequestValidateAuthenticationKeyWithUserInfo* createRequestValidateAuthenticationKeyWithUserInfo() = 0;
		virtual IResponseValidateAuthenticationKeyWithUserInfo* createResponseValidateAuthenticationKeyWithUserInfo() = 0;
		virtual bool sendSync(IRequestValidateAuthenticationKeyWithUserInfo* req, IResponseValidateAuthenticationKeyWithUserInfo* res) = 0;
		virtual bool sendAsync(IRequestValidateAuthenticationKeyWithUserInfo* req) = 0;

		// Authentication & Authorization Step 12: Account Login : ���� �α���		
		virtual IRequestAccountLogin* createRequestAccountLogin() = 0;
		virtual IResponseAccountLogin* createResponseAccountLogin() = 0;
		virtual bool sendSync(IRequestAccountLogin* req, IResponseAccountLogin* res) = 0;
		virtual bool sendAsync(IRequestAccountLogin* req) = 0;

		// Authentication & Authorization Step 13: Account Logout : ���� �α׾ƿ�
		virtual IRequestAccountLogout* createRequestAccountLogout() = 0;
		virtual IResponseAccountLogout* createResponseAccountLogout() = 0;
		virtual bool sendSync(IRequestAccountLogout* req, IResponseAccountLogout* res) = 0;
		virtual bool sendAsync(IRequestAccountLogout* req) = 0;

		// Authentication & Authorization Step 14: Set Account State : ������ ������ �α���/�α׾ƿ� ���� ��ȣ, IP, �ð�, �����α��� Ƚ�� ������Ʈ
		virtual IRequestSetAccountState* createRequestSetAccountState() = 0;
		virtual IResponseSetAccountState* createResponseSetAccountState() = 0;
		virtual bool sendSync(IRequestSetAccountState* req, IResponseSetAccountState* res) = 0;
		virtual bool sendAsync(IRequestSetAccountState* req) = 0;

		// Authentication & Authorization Step 15: Get PC Room Guid : IP�� PC�� ������ȣ ��ȯ
		virtual IRequestGetPCRoomGuid* createRequestGetPCRoomGuid() = 0;
		virtual IResponseGetPCRoomGuid* createResponseGetPCRoomGuid() = 0;
		virtual bool sendSync(IRequestGetPCRoomGuid* req, IResponseGetPCRoomGuid* res) = 0;
		virtual bool sendAsync(IRequestGetPCRoomGuid* req) = 0;

		// Authentication & Authorization Step 16: Check Phone Auth User : ��ȭ���� ���԰��� ���� Ȯ��
		virtual IRequestCheckPhoneAuthUser* createRequestCheckPhoneAuthUser() = 0;
		virtual IResponseCheckPhoneAuthUser* createResponseCheckPhoneAuthUser() = 0;
		virtual bool sendSync(IRequestCheckPhoneAuthUser* req, IResponseCheckPhoneAuthUser* res) = 0;
		virtual bool sendAsync(IRequestCheckPhoneAuthUser* req) = 0;

		// Authentication & Authorization Step 17: Get User Info : ������ȣ�� ����� ���� Ȯ��
		virtual IRequestGetUserInfo* createRequestGetUserInfo() = 0;
		virtual IResponseGetUserInfo* createResponseGetUserInfo() = 0;
		virtual bool sendSync(IRequestGetUserInfo* req, IResponseGetUserInfo* res) = 0;
		virtual bool sendAsync(IRequestGetUserInfo* req) = 0;

		// Authentication & Authorization Step 18: Get User Info With Extension : ������ȣ�� ����� ���� Ȯ��
		virtual IRequestGetUserInfoWithExtension* createRequestGetUserInfoWithExtension() = 0;
		virtual IResponseGetUserInfoWithExtension* createResponseGetUserInfoWithExtension() = 0;
		virtual bool sendSync(IRequestGetUserInfoWithExtension* req, IResponseGetUserInfoWithExtension* res) = 0;
		virtual bool sendAsync(IRequestGetUserInfoWithExtension* req) = 0;

		// ���� C9�� ���� ������ �������̽�
		// Authentication & Authorization Step 6: Validate Authentication Key : ����Ű ��ȿ�� �˻�
		virtual bool validateAuthenticationKey(int user_no, wchar_t* authentication_key, wchar_t* client_ip)=0;
		// Authentication & Authorization Step 7: Validate Authentication Key with Extension : ����Ű ��ȿ�� �˻�
		virtual bool validateAuthenticationKeyWithExtension(int account_no, wchar_t* authentication_key, wchar_t* client_ip,
															int& res_user_no, wchar_t* res_user_id, int res_user_id_len,
															int& res_account_no, wchar_t* res_account_id, int res_account_id_len,
															byte& res_channel_info)=0;
	};

	// Basic Billing : thread unsafe
	class IBasicBilling : public IObject
	{
	public:
		IBasicBilling(){}
		virtual ~IBasicBilling(){}

	public:
		// Basic Billing Step 1: Check Balance : �ܾ���ȸ
		virtual IRequestCheckBalance*	createRequestCheckBalance()		= 0;
		virtual IResponseCheckBalance*	createResponseCheckBalance()	= 0;
		virtual bool sendSync(IRequestCheckBalance* req, IResponseCheckBalance* res) = 0;	// ��� ���н� false ����
		virtual bool sendAsync(IRequestCheckBalance* req) = 0;

		// Basic Billing Step 2: Item Purchase : ������ ����
		virtual IRequestItemPurchase*	createRequestItemPurchase()		= 0;
		virtual IResponseItemPurchase*	createResponseItemPurchase()	= 0;
		virtual bool sendSync(IRequestItemPurchase* req, IResponseItemPurchase* res) = 0;
		virtual bool sendAsync(IRequestItemPurchase* req) = 0;

		// Basic Billing Step 3: Item Gift : ������ ����
		virtual IRequestItemGift* createRequestItemGift()				= 0;
		virtual IResponseItemGift* createResponseItemGift()				= 0;
		virtual bool sendSync(IRequestItemGift* req, IResponseItemGift* res) = 0;
		virtual bool sendAsync(IRequestItemGift* req) = 0;
		
		// Basic Billing Step 4: Check Purchase : ���� Ȯ��
		virtual IRequestCheckPurchase*	createRequestCheckPurchase()	= 0;
		virtual IResponseCheckPurchase*	createResponseCheckPurchase()	= 0;
		virtual bool sendSync(IRequestCheckPurchase* req, IResponseCheckPurchase* res) = 0;
		virtual bool sendAsync(IRequestCheckPurchase* req) = 0;

		// Basic Billing Step 5: Cancel Purchase : ���� ���
		virtual IRequestCancelPurchase* createRequestCancelPurchase()	= 0;
		virtual IResponseCancelPurchase* createResponseCancelPurchase()	= 0;
		virtual bool sendSync(IRequestCancelPurchase* req, IResponseCancelPurchase* res) = 0;
		virtual bool sendAsync(IRequestCancelPurchase* req) = 0;

		// Basic Billing Step 6: Cancel Purchase by Order Id : �ֹ���ȣ�� �̿��ؼ� ��ü ���� ���
		virtual IRequestCancelPurchaseByOrderId*	createRequestCancelPurchaseByOrderId()	= 0;
		virtual IResponseCancelPurchaseByOrderId*	createResponseCancelPurchaseByOrderId()	= 0;
		virtual bool sendSync(IRequestCancelPurchaseByOrderId* req, IResponseCancelPurchaseByOrderId* res) = 0;
		virtual bool sendAsync(IRequestCancelPurchaseByOrderId* req) = 0;

		// Basic Billing Step 7: Confirm Purchase by Order Id : �ֹ���ȣ�� �̿��ؼ� ��ü ���� ����
		virtual IRequestConfirmPurchaseByOrderId*	createRequestConfirmPurchaseByOrderId()		= 0;
		virtual IResponseConfirmPurchaseByOrderId*	createResponseConfirmPurchaseByOrderId()	= 0;
		virtual bool sendSync(IRequestConfirmPurchaseByOrderId* req, IResponseConfirmPurchaseByOrderId* res) = 0;
		virtual bool sendAsync(IRequestConfirmPurchaseByOrderId* req) = 0;

		// Basic Billing Step 8: Purchase List : ���ų��� ��ȸ
		virtual IRequestPurchaseList* createRequestPurchaseList()	= 0;
		virtual IResponsePurchaseList* createResponsePurchaseList()	= 0;
		virtual bool sendSync(IRequestPurchaseList* req, IResponsePurchaseList* res) = 0;
		virtual bool sendAsync(IRequestPurchaseList* req) = 0;

		// Basic Billing Step 9: Exchange WCoin : WCoin�� ���� ������ ���Ǵ� ����Ʈ�� ��ȯ
		virtual IRequestExchangeWCoin* createRequestExchangeWCoin()		= 0;
		virtual IResponseExchangeWCoin* createResponseExchangeWCoin()	= 0;
		virtual bool sendSync(IRequestExchangeWCoin* req, IResponseExchangeWCoin* res) = 0;
		virtual bool sendAsync(IRequestExchangeWCoin* req) = 0;
	};

	// WShop Billing : thread unsafe
	class IWShopBilling : public IObject
	{
	public:
		IWShopBilling() {}
		virtual ~IWShopBilling() {}

	public:
		// WShop Billing Step 1 : WShop Check Balance : �ܾ���ȸ
		virtual IRequestWShopCheckBalance*	createRequestWShopCheckBalance()= 0;
		virtual IResponseWShopCheckBalance*	createResponseWShopCheckBalance()= 0;
		virtual bool sendSync(IRequestWShopCheckBalance* req, IResponseWShopCheckBalance* res)= 0;
		virtual bool sendAsync(IRequestWShopCheckBalance* req)= 0;
		// WShop Billing Step 2 : WShopPurchase : �� ������ ����
		virtual IRequestWShopPurchase*	createRequestWShopPurchase()= 0;
		virtual IResponseWShopPurchase*	createResponseWShopPurchase()= 0;
		virtual bool sendSync(IRequestWShopPurchase* req, IResponseWShopPurchase* res)= 0;
		virtual bool sendAsync(IRequestWShopPurchase* req)= 0;
		// WShop Billing Step 3 : WShopCheckPurchase : �� ������ ���� Ȯ��
		virtual IRequestWShopCheckPurchase*	createRequestWShopCheckPurchase()= 0;
		virtual IResponseWShopCheckPurchase*	createResponseWShopCheckPurchase()= 0;
		virtual bool sendSync(IRequestWShopCheckPurchase* req, IResponseWShopCheckPurchase* res)= 0;
		virtual bool sendAsync(IRequestWShopCheckPurchase* req)= 0;
		// WShop Billing Step 4 : WShopCancelPurchase : �� ������ ���� ���
		virtual IRequestWShopCancelPurchase*	createRequestWShopCancelPurchase()= 0;
		virtual IResponseWShopCancelPurchase*	createResponseWShopCancelPurchase()= 0;
		virtual bool sendSync(IRequestWShopCancelPurchase* req, IResponseWShopCancelPurchase* res)= 0;
		virtual bool sendAsync(IRequestWShopCancelPurchase* req)= 0;
		// WShop Billing Step 5 : WShopConfirmPurchase : �� ������ ���� ����
		virtual IRequestWShopConfirmPurchase*	createRequestWShopConfirmPurchase()= 0;
		virtual IResponseWShopConfirmPurchase*	createResponseWShopConfirmPurchase()= 0;
		virtual bool sendSync(IRequestWShopConfirmPurchase* req, IResponseWShopConfirmPurchase* res)= 0;
		virtual bool sendAsync(IRequestWShopConfirmPurchase* req)= 0;
		// WShop Billing Step 6 : WShopGift : �� ������ ����
		virtual IRequestWShopGift*	createRequestWShopGift()= 0;
		virtual IResponseWShopGift*	createResponseWShopGift()= 0;
		virtual bool sendSync(IRequestWShopGift* req, IResponseWShopGift* res)= 0;
		virtual bool sendAsync(IRequestWShopGift* req)= 0;
		// WShop Billing Step 7 : WShopCheckGift : ���� �� Ȯ��
		virtual IRequestWShopCheckGift*	createRequestWShopCheckGift()= 0;
		virtual IResponseWShopCheckGift*	createResponseWShopCheckGift()= 0;
		virtual bool sendSync(IRequestWShopCheckGift* req, IResponseWShopCheckGift* res)= 0;
		virtual bool sendAsync(IRequestWShopCheckGift* req)= 0;
		// WShop Billing Step 8 : WShopCancelGift : ���� �� ���
		virtual IRequestWShopCancelGift*	createRequestWShopCancelGift()= 0;
		virtual IResponseWShopCancelGift*	createResponseWShopCancelGift()= 0;
		virtual bool sendSync(IRequestWShopCancelGift* req, IResponseWShopCancelGift* res)= 0;
		virtual bool sendAsync(IRequestWShopCancelGift* req)= 0;
		// WShop Billing Step 9 : WShopConfirmGift : ��� ���� �� ����
		virtual IRequestWShopConfirmGift*	createRequestWShopConfirmGift()= 0;
		virtual IResponseWShopConfirmGift*	createResponseWShopConfirmGift()= 0;
		virtual bool sendSync(IRequestWShopConfirmGift* req, IResponseWShopConfirmGift* res)= 0;
		virtual bool sendAsync(IRequestWShopConfirmGift* req)= 0;
		// WShop Billing Step 10 : WShopGetVersion : �� ���� ���� ��ȸ
		virtual IRequestWShopGetVersion*	createRequestWShopGetVersion()= 0;
		virtual IResponseWShopGetVersion*	createResponseWShopGetVersion()= 0;
		virtual bool sendSync(IRequestWShopGetVersion* req, IResponseWShopGetVersion* res)= 0;
		virtual bool sendAsync(IRequestWShopGetVersion* req)= 0;
	};

	// WShop Inventory : thread unsafe
	class IWShopInventory : public IObject
	{
	public:
		IWShopInventory() {}
		virtual ~IWShopInventory() {}

	public:
		// WShop Inventory Step 1 : WShop Inquiry New Arrival : ���� �������� ���� ���� �κ��丮 ������ ��ȸ
		virtual IRequestWShopInquiryNewArrival*	createRequestWShopInquiryNewArrival()= 0;
		virtual IResponseWShopInquiryNewArrival*	createResponseWShopInquiryNewArrival()= 0;
		virtual bool sendSync(IRequestWShopInquiryNewArrival* req, IResponseWShopInquiryNewArrival* res)= 0;
		virtual bool sendAsync(IRequestWShopInquiryNewArrival* req)= 0;
		// WShop Inventory Step 2 : WShop Inquiry Inventory : �κ��丮 ��ȸ
		virtual IRequestWShopInquiryInventory*	createRequestWShopInquiryInventory()= 0;
		virtual IResponseWShopInquiryInventory*	createResponseWShopInquiryInventory()= 0;
		virtual bool sendSync(IRequestWShopInquiryInventory* req, IResponseWShopInquiryInventory* res)= 0;
		virtual bool sendAsync(IRequestWShopInquiryInventory* req)= 0;
		// WShop Inventory Step 3 : WShop Pick Up : �κ��丮 ����
		virtual IRequestWShopPickUp*	createRequestWShopPickUp()= 0;
		virtual IResponseWShopPickUp*	createResponseWShopPickUp()= 0;
		virtual bool sendSync(IRequestWShopPickUp* req, IResponseWShopPickUp* res)= 0;
		virtual bool sendAsync(IRequestWShopPickUp* req)= 0;
		// WShop Inventory Step 4 : WShop Check Pick Up : �κ��丮 ���� �� Ȯ��
		virtual IRequestWShopCheckPickUp*	createRequestWShopCheckPickUp()= 0;
		virtual IResponseWShopCheckPickUp*	createResponseWShopCheckPickUp()= 0;
		virtual bool sendSync(IRequestWShopCheckPickUp* req, IResponseWShopCheckPickUp* res)= 0;
		virtual bool sendAsync(IRequestWShopCheckPickUp* req)= 0;
		// WShop Inventory Step 5 : WShop Cancel Pick Up : �κ��丮���ɰ����
		virtual IRequestWShopCancelPickUp*	createRequestWShopCancelPickUp()= 0;
		virtual IResponseWShopCancelPickUp*	createResponseWShopCancelPickUp()= 0;
		virtual bool sendSync(IRequestWShopCancelPickUp* req, IResponseWShopCancelPickUp* res)= 0;
		virtual bool sendAsync(IRequestWShopCancelPickUp* req)= 0;
		// WShop Inventory Step 6 : WShop Confirm Pick Up : �κ��丮���ɰǽ���
		virtual IRequestWShopConfirmPickUp*	createRequestWShopConfirmPickUp()= 0;
		virtual IResponseWShopConfirmPickUp*	createResponseWShopConfirmPickUp()= 0;
		virtual bool sendSync(IRequestWShopConfirmPickUp* req, IResponseWShopConfirmPickUp* res)= 0;
		virtual bool sendAsync(IRequestWShopConfirmPickUp* req)= 0;
	};

	// Jewel : thread unsafe
	class IJewel : public IObject
	{
	public:
		IJewel(){}
		virtual ~IJewel(){}

	public:
		// Jewel Step 1  : Charge Jewel : ���������û
		virtual IRequestChargeJewel*	createRequestChargeJewel()= 0;
		virtual IResponseChargeJewel*	createResponseChargeJewel()= 0;
		virtual bool sendSync(IRequestChargeJewel* req, IResponseChargeJewel* res)= 0;
		virtual bool sendAsync(IRequestChargeJewel* req)= 0;
		// Jewel Step 2  : Check Jewel Charge : ���������Ȯ��
		virtual IRequestCheckJewelCharge*	createRequestCheckJewelCharge()= 0;
		virtual IResponseCheckJewelCharge*	createResponseCheckJewelCharge()= 0;
		virtual bool sendSync(IRequestCheckJewelCharge* req, IResponseCheckJewelCharge* res)= 0;
		virtual bool sendAsync(IRequestCheckJewelCharge* req)= 0;
		// Jewel Step 3  : Cancel Jewel Charge : ������������
		virtual IRequestCancelJewelCharge*	createRequestCancelJewelCharge()= 0;
		virtual IResponseCancelJewelCharge*	createResponseCancelJewelCharge()= 0;
		virtual bool sendSync(IRequestCancelJewelCharge* req, IResponseCancelJewelCharge* res)= 0;
		virtual bool sendAsync(IRequestCancelJewelCharge* req)= 0;
		// Jewel Step 4  : Confirm Jewel Charge : ��������ǽ���
		virtual IRequestConfirmJewelCharge*	createRequestConfirmJewelCharge()= 0;
		virtual IResponseConfirmJewelCharge*	createResponseConfirmJewelCharge()= 0;
		virtual bool sendSync(IRequestConfirmJewelCharge* req, IResponseConfirmJewelCharge* res)= 0;
		virtual bool sendAsync(IRequestConfirmJewelCharge* req)= 0;
		// Jewel Step 5  : Purchase Jewel Item : ������
		virtual IRequestPurchaseJewelItem*	createRequestPurchaseJewelItem()= 0;
		virtual IResponsePurchaseJewelItem*	createResponsePurchaseJewelItem()= 0;
		virtual bool sendSync(IRequestPurchaseJewelItem* req, IResponsePurchaseJewelItem* res)= 0;
		virtual bool sendAsync(IRequestPurchaseJewelItem* req)= 0;
		// Jewel Step 6  : Check Purchase Jewel : ��������Ȯ��
		virtual IRequestCheckPurchaseJewel*	createRequestCheckPurchaseJewel()= 0;
		virtual IResponseCheckPurchaseJewel*	createResponseCheckPurchaseJewel()= 0;
		virtual bool sendSync(IRequestCheckPurchaseJewel* req, IResponseCheckPurchaseJewel* res)= 0;
		virtual bool sendAsync(IRequestCheckPurchaseJewel* req)= 0;
		// Jewel Step 7  : Cancel Jewel Purchase : �����������
		virtual IRequestCancelJewelPurchase*	createRequestCancelJewelPurchase()= 0;
		virtual IResponseCancelJewelPurchase*	createResponseCancelJewelPurchase()= 0;
		virtual bool sendSync(IRequestCancelJewelPurchase* req, IResponseCancelJewelPurchase* res)= 0;
		virtual bool sendAsync(IRequestCancelJewelPurchase* req)= 0;
		// Jewel Step 8  : Confirm Jewel Purchase : �������ǽ���
		virtual IRequestConfirmJewelPurchase*	createRequestConfirmJewelPurchase()= 0;
		virtual IResponseConfirmJewelPurchase*	createResponseConfirmJewelPurchase()= 0;
		virtual bool sendSync(IRequestConfirmJewelPurchase* req, IResponseConfirmJewelPurchase* res)= 0;
		virtual bool sendAsync(IRequestConfirmJewelPurchase* req)= 0;
		// Jewel Step 9  : Trade Jewel : �������ŷ�
		virtual IRequestTradeJewel*	createRequestTradeJewel()= 0;
		virtual IResponseTradeJewel*	createResponseTradeJewel()= 0;
		virtual bool sendSync(IRequestTradeJewel* req, IResponseTradeJewel* res)= 0;
		virtual bool sendAsync(IRequestTradeJewel* req)= 0;
		// Jewel Step 10 : Check Trade Jewel : �������ŷ���Ȯ�� 
		virtual IRequestCheckTradeJewel*	createRequestCheckTradeJewel()= 0;
		virtual IResponseCheckTradeJewel*	createResponseCheckTradeJewel()= 0;
		virtual bool sendSync(IRequestCheckTradeJewel* req, IResponseCheckTradeJewel* res)= 0;
		virtual bool sendAsync(IRequestCheckTradeJewel* req)= 0;
		// Jewel Step 11 : Cancel Jewel Trade : �������ŷ������
		virtual IRequestCancelJewelTrade*	createRequestCancelJewelTrade()= 0;
		virtual IResponseCancelJewelTrade*	createResponseCancelJewelTrade()= 0;
		virtual bool sendSync(IRequestCancelJewelTrade* req, IResponseCancelJewelTrade* res)= 0;
		virtual bool sendAsync(IRequestCancelJewelTrade* req)= 0;
		// Jewel Step 12 : Confirm Jewel Trade : ��� ����� �ŷ��� ����
		virtual IRequestConfirmJewelTrade*	createRequestConfirmJewelTrade()= 0;
		virtual IResponseConfirmJewelTrade*	createResponseConfirmJewelTrade()= 0;
		virtual bool sendSync(IRequestConfirmJewelTrade* req, IResponseConfirmJewelTrade* res)= 0;
		virtual bool sendAsync(IRequestConfirmJewelTrade* req)= 0;
		// Jewel Step 13 : Pick Up Trade Jewel : ��� ����� �Ǹűݾ� ����(�Ǹ���)
		virtual IRequestPickUpTradeJewel*	createRequestPickUpTradeJewel()= 0;
		virtual IResponsePickUpTradeJewel*	createResponsePickUpTradeJewel()= 0;
		virtual bool sendSync(IRequestPickUpTradeJewel* req, IResponsePickUpTradeJewel* res)= 0;
		virtual bool sendAsync(IRequestPickUpTradeJewel* req)= 0;
		// Jewel Step 14 : Check Trade Jewel Pick Up : ����� �Ǹűݾ� ���ɰ� Ȯ��
		virtual IRequestCheckTradeJewelPickUp*	createRequestCheckTradeJewelPickUp()= 0;
		virtual IResponseCheckTradeJewelPickUp*	createResponseCheckTradeJewelPickUp()= 0;
		virtual bool sendSync(IRequestCheckTradeJewelPickUp* req, IResponseCheckTradeJewelPickUp* res)= 0;
		virtual bool sendAsync(IRequestCheckTradeJewelPickUp* req)= 0;
		// Jewel Step 15 : Cancel Trade Jewel Pick Up : ����� �Ǹűݾ� ���ɰ� ���
		virtual IRequestCancelTradeJewelPickUp*	createRequestCancelTradeJewelPickUp()= 0;
		virtual IResponseCancelTradeJewelPickUp*	createResponseCancelTradeJewelPickUp()= 0;
		virtual bool sendSync(IRequestCancelTradeJewelPickUp* req, IResponseCancelTradeJewelPickUp* res)= 0;
		virtual bool sendAsync(IRequestCancelTradeJewelPickUp* req)= 0;
		// Jewel Step 16 : Confirm Trade Jewel Pick Up : ����� �Ǹűݾ� ���ɰ� ����
		virtual IRequestConfirmTradeJewelPickUp*	createRequestConfirmTradeJewelPickUp()= 0;
		virtual IResponseConfirmTradeJewelPickUp*	createResponseConfirmTradeJewelPickUp()= 0;
		virtual bool sendSync(IRequestConfirmTradeJewelPickUp* req, IResponseConfirmTradeJewelPickUp* res)= 0;
		virtual bool sendAsync(IRequestConfirmTradeJewelPickUp* req)= 0;
	};

	// Advanced Billing - Cash Inventory : thread unsafe
	class ICashInventory : public IObject
	{
	public:
		ICashInventory(){}
		virtual ~ICashInventory(){}

		// Cash Inventory Step 1: Inquiry Cash Inventory - ĳ���κ��丮��ȸ
		virtual IRequestInquiryCashInventory*	createRequestInquiryCashInventory()		= 0;
		virtual IResponseInquiryCashInventory*	createResponseInquiryCashInventory()	= 0;
		virtual bool sendSync(IRequestInquiryCashInventory* req, IResponseInquiryCashInventory* res) = 0;
		virtual bool sendAsync(IRequestInquiryCashInventory* req) = 0;

		// Cash Inventory Step 2: Inquiry Cash Inventory by Bind Attribute - ������ �ͼ� ���¿� ���� ĳ���κ��丮��ȸ
		virtual IRequestInquiryCashInventoryByBindAttribute*	createRequestInquiryCashInventoryByBindAttribute()	= 0;
		virtual IResponseInquiryCashInventoryByBindAttribute*	createResponseInquiryCashInventoryByBindAttribute()	= 0;
		virtual bool sendSync(IRequestInquiryCashInventoryByBindAttribute* req, IResponseInquiryCashInventoryByBindAttribute* res)	= 0;
		virtual bool sendAsync(IRequestInquiryCashInventoryByBindAttribute* req)	= 0;

		// Cash Inventory Step 3: Pickup Cash Inventory Item - ĳ���κ��丮����
		virtual IRequestPickupCashInventoryItem*	createRequestPickupCashInventoryItem()	= 0;
		virtual IResponsePickupCashInventoryItem*	createResponsePickupCashInventoryItem()	= 0;
		virtual bool sendSync(IRequestPickupCashInventoryItem* req, IResponsePickupCashInventoryItem* res) = 0;
		virtual bool sendAsync(IRequestPickupCashInventoryItem* req) = 0;

		// Cash Inventory Step 4: Pickup Cash Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ĳ���κ��丮����
		virtual IRequestPickupCashInventoryItemByBindAttribute*		createRequestPickupCashInventoryItemByBindAttribute()	= 0;
		virtual IResponsePickupCashInventoryItemByBindAttribute*	createResponsePickupCashInventoryItemByBindAttribute()	= 0;
		virtual bool sendSync(IRequestPickupCashInventoryItemByBindAttribute* req, IResponsePickupCashInventoryItemByBindAttribute* res)	= 0;
		virtual bool sendAsync(IRequestPickupCashInventoryItemByBindAttribute* req)	= 0;

		// Cash Inventory Step 5: Cancel Pickup Cash Inventory Item - ĳ���κ��丮�������
		virtual IRequestCancelCashInventoryItem*	createRequestCancelCashInventoryItem()	= 0;
		virtual IResponseCancelCashInventoryItem*	createResponseCancelCashInventoryItem()	= 0;
		virtual bool sendSync(IRequestCancelCashInventoryItem* req, IResponseCancelCashInventoryItem* res) = 0;
		virtual bool sendAsync(IRequestCancelCashInventoryItem* req) = 0;

		// Cash Inventory Step 6: Cancel Pickup Cash Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ĳ���κ��丮�������
		virtual IRequestCancelCashInventoryItemByBindAttribute*		createRequestCancelCashInventoryItemByBindAttribute()	= 0;
		virtual IResponseCancelCashInventoryItemByBindAttribute*	createResponseCancelCashInventoryItemByBindAttribute()	= 0;
		virtual bool sendSync(IRequestCancelCashInventoryItemByBindAttribute* req, IResponseCancelCashInventoryItemByBindAttribute* res)	= 0;
		virtual bool sendAsync(IRequestCancelCashInventoryItemByBindAttribute* req)	= 0;

		// Cash Inventory Step 7: Pickup Cash Sub Inventory Item - ����ĳ���κ��丮����
		virtual IRequestPickupCashSubInventoryItem*		createRequestPickupCashSubInventoryItem()	= 0;
		virtual IResponsePickupCashSubInventoryItem*	createResponsePickupCashSubInventoryItem()	= 0;
		virtual bool sendSync(IRequestPickupCashSubInventoryItem* req, IResponsePickupCashSubInventoryItem* res) = 0;
		virtual bool sendAsync(IRequestPickupCashSubInventoryItem* req) = 0;

		// Cash Inventory Step 8: Pickup Cash Sub Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ����ĳ���κ��丮����
		virtual IRequestPickupCashSubInventoryItemByBindAttribute*		createRequestPickupCashSubInventoryItemByBindAttribute()	= 0;
		virtual IResponsePickupCashSubInventoryItemByBindAttribute*		createResponsePickupCashSubInventoryItemByBindAttribute()	= 0;
		virtual bool sendSync(IRequestPickupCashSubInventoryItemByBindAttribute* req, IResponsePickupCashSubInventoryItemByBindAttribute* res)	= 0;
		virtual bool sendAsync(IRequestPickupCashSubInventoryItemByBindAttribute* req)	= 0;

		// Cash Inventory Step 9: Cancel Cash Sub Inventory Item - ����ĳ���κ��丮���
		virtual IRequestCancelCashSubInventoryItem*		createRequestCancelCashSubInventoryItem()	= 0;
		virtual IResponseCancelCashSubInventoryItem*	createResponseCancelCashSubInventoryItem()	= 0;
		virtual bool sendSync(IRequestCancelCashSubInventoryItem* req, IResponseCancelCashSubInventoryItem* res) = 0;
		virtual bool sendAsync(IRequestCancelCashSubInventoryItem* req) = 0;

		// Cash Inventory Step 10: Cancel Cash Sub Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ����ĳ���κ��丮���
		virtual IRequestCancelCashSubInventoryItemByBindAttribute*		createRequestCancelCashSubInventoryItemByBindAttribute()	= 0;
		virtual IResponseCancelCashSubInventoryItemByBindAttribute*		createResponseCancelCashSubInventoryItemByBindAttribute()	= 0;
		virtual bool sendSync(IRequestCancelCashSubInventoryItemByBindAttribute* req, IResponseCancelCashSubInventoryItemByBindAttribute* res)	= 0;
		virtual bool sendAsync(IRequestCancelCashSubInventoryItemByBindAttribute* req)	= 0;

		// Cash Inventory Step 11: Inquiry Pickup Standby Cash Purchase No - ���ӿ��� ���� ������ ������ ���Ź�ȣ ����Ʈ ��ȸ
		virtual IRequestInquiryPickupStandbyCashPurchaseNo* createRequestInquiryPickupStandbyCashPurchaseNo()	= 0;
		virtual IResponseInquiryPickupStandbyCashPurchaseNo* createResponseInquiryPickupStandbyCashPurchaseNo()	= 0;
		virtual bool sendSync(IRequestInquiryPickupStandbyCashPurchaseNo* req, IResponseInquiryPickupStandbyCashPurchaseNo* res)	= 0;
		virtual bool sendAsync(IRequestInquiryPickupStandbyCashPurchaseNo* req)	= 0;

		// Cash Inventory Step 12: Pickup Standby Cash Inventory Item - ���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �����·� ��ȯ
		virtual IRequestPickupStandbyCashInventory* createRequestPickupStandbyCashInventory()	= 0;
		virtual IResponsePickupStandbyCashInventory* createResponsePickupStandbyCashInventory()	= 0;
		virtual bool sendSync(IRequestPickupStandbyCashInventory* req, IResponsePickupStandbyCashInventory* res)	= 0;
		virtual bool sendAsync(IRequestPickupStandbyCashInventory* req)	= 0;

		// Cash Inventory Step 13: Complete Pickup Standby Cash Inventory - ���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �Ϸ���·� ��ȯ
		virtual IRequestCompletePickupStandbyCashInventory* createRequestCompletePickupStandbyCashInventory()	= 0;
		virtual IResponseCompletePickupStandbyCashInventory* createResponseCompletePickupStandbyCashInventory()	= 0;
		virtual bool sendSync(IRequestCompletePickupStandbyCashInventory* req, IResponseCompletePickupStandbyCashInventory* res)	= 0;
		virtual bool sendAsync(IRequestCompletePickupStandbyCashInventory* req)	= 0;

		// Cash Inventory Step 14: Cancel Pickup Standby Cash Inventory - ���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �����¿��� ���
		virtual IRequestCancelPickupStandbyCashInventory* createRequestCancelPickupStandbyCashInventory()	= 0;
		virtual IResponseCancelPickupStandbyCashInventory* createResponseCancelPickupStandbyCashInventory()	= 0;
		virtual bool sendSync(IRequestCancelPickupStandbyCashInventory* req, IResponseCancelPickupStandbyCashInventory* res)	= 0;
		virtual bool sendAsync(IRequestCancelPickupStandbyCashInventory* req)	= 0;

		// Cash Inventory Step 15: Use Storage - IBS ������ ��ǰ ���
		virtual IRequestUseStorage* createRequestUseStorage() = 0;
		virtual IResponseUseStorage* createResponseUseStorage() = 0;
		virtual bool sendSync(IRequestUseStorage* req, IResponseUseStorage* res) = 0;
		virtual bool sendAsync(IRequestUseStorage* req) = 0;

		// Cash INventory Step 16: Rollback Use Storage - IBS ������ ��� �ѹ�
		virtual IRequestRollbackUseStorage* createRequestRollbackUseStorage() = 0;
		virtual IResponseRollbackUseStorage* createResponseRollbackUseStorage() = 0;
		virtual bool sendSync(IRequestRollbackUseStorage* req, IResponseRollbackUseStorage* res) = 0;
		virtual bool sendAsync(IRequestRollbackUseStorage* req) = 0;
	};

	// Advanced Billing - Inquiry OData : thread unsafe
	class IInquiryOData : public IObject
	{
	public:
		IInquiryOData(){}
		virtual ~IInquiryOData(){}
		
		// Inquiry OData Step 1: Inquiry Service Metadata : Metadata ��ȸ
		virtual IRequestInquiryServiceMetadata*		createRequestInquiryServiceMetadata()	= 0;
		virtual IResponseInquiryServiceMetadata*	createResponseInquiryServiceMetadata()	= 0;
		virtual bool sendSync(IRequestInquiryServiceMetadata* req, IResponseInquiryServiceMetadata* res) = 0;
		virtual bool sendAsync(IRequestInquiryServiceMetadata* req) = 0;
		
		// Inquiry OData Step 2: Inquiry OData Service: OData ��ȸ
		virtual IRequestInquiryODataService*	createRequestInquiryODataService()	= 0;
		virtual IResponseInquiryODataService*	createResponseInquiryODataService()	= 0;
		virtual bool sendSync(IRequestInquiryODataService* req, IResponseInquiryODataService* res) = 0;
		virtual bool sendAsync(IRequestInquiryODataService* req) = 0;
	};

	// Advanced Billing - Cart & Wish Items : thread unsafe
	class ICartAndWishItems : public IObject
	{
	public:
		ICartAndWishItems(){}
		virtual ~ICartAndWishItems(){}
		
		// Cart & Wish Items Step 1: Inquiry Cart Items : ����īƮ��ȸ
		virtual IRequestInquiryCartItems*	createRequestInquiryCartItems()		= 0;
		virtual IResponseInquiryCartItems*	createResponseInquiryCartItems()	= 0;
		virtual bool sendSync(IRequestInquiryCartItems* req, IResponseInquiryCartItems* res) = 0;
		virtual bool sendAsync(IRequestInquiryCartItems* req) = 0;
		
		// Cart & Wish Items Step 2: Register Cart Items : ����īƮ��ǰ���
		virtual IRequestRegisterCartItems*	createRequestRegisterCartItems()	= 0;
		virtual IResponseRegisterCartItems*	createResponseRegisterCartItems()	= 0;
		virtual bool sendSync(IRequestRegisterCartItems* req, IResponseRegisterCartItems* res) = 0;
		virtual bool sendAsync(IRequestRegisterCartItems* req) = 0;
		
		// Cart & Wish Items Step 3: Modify Cart Items Quantity : ����īƮ�����ۺ���
		virtual IRequestModifyCartItemsQuantity*	createRequestModifyCartItemsQuantity()	= 0;
		virtual IResponseModifyCartItemsQuantity*	createResponseModifyCartItemsQuantity()	= 0;
		virtual bool sendSync(IRequestModifyCartItemsQuantity* req, IResponseModifyCartItemsQuantity* res) = 0;
		virtual bool sendAsync(IRequestModifyCartItemsQuantity* req) = 0;
		
		// Cart & Wish Items Step 4: Modify Cart Items Attribute : ����īƮ�����ۺ���
		virtual IRequestModifyCartItemsAttribute*	createRequestModifyCartItemsAttribute()	= 0;
		virtual IResponseModifyCartItemsAttribute*	createResponseModifyCartItemsAttribute()	= 0;
		virtual bool sendSync(IRequestModifyCartItemsAttribute* req, IResponseModifyCartItemsAttribute* res) = 0;
		virtual bool sendAsync(IRequestModifyCartItemsAttribute* req) = 0;
		
		// Cart & Wish Items Step 5: Remove Cart Items : ����īƮ�����ۻ���	
		virtual IRequestRemoveCartItems*	createRequestRemoveCartItems()	= 0;
		virtual IResponseRemoveCartItems*	createResponseRemoveCartItems()	= 0;
		virtual bool sendSync(IRequestRemoveCartItems* req, IResponseRemoveCartItems* res) = 0;
		virtual bool sendAsync(IRequestRemoveCartItems* req) = 0;
		
		// Cart & Wish Items Step 6: Remove Cart : ����īƮ�ʱ�ȭ
		virtual IRequestRemoveCart*		createRequestRemoveCart()	= 0;
		virtual IResponseRemoveCart*	createResponseRemoveCart()	= 0;
		virtual bool sendSync(IRequestRemoveCart* req, IResponseRemoveCart* res) = 0;
		virtual bool sendAsync(IRequestRemoveCart* req) = 0;
		
		// Cart & Wish Items Step 7: Cart Items Transfer Wish Items : ���þ��������� ����īƮ ������ �̵�
		virtual IRequestCartItemsTransferWishItems*		createRequestCartItemsTransferWishItems()	= 0;
		virtual IResponseCartItemsTransferWishItems*	createResponseCartItemsTransferWishItems()	= 0;
		virtual bool sendSync(IRequestCartItemsTransferWishItems* req, IResponseCartItemsTransferWishItems* res) = 0;
		virtual bool sendAsync(IRequestCartItemsTransferWishItems* req) = 0;
		
		// Cart & Wish Items Step 8: Inquiry Wish Items : ���þ�������ȸ
		virtual IRequestInquiryWishItems*	createRequestInquiryWishItems()		= 0;
		virtual IResponseInquiryWishItems*	createResponseInquiryWishItems()	= 0;
		virtual bool sendSync(IRequestInquiryWishItems* req, IResponseInquiryWishItems* res) = 0;
		virtual bool sendAsync(IRequestInquiryWishItems* req) = 0;
		
		// Cart & Wish Items Step 9: Register Wish Items : Wish ����Ʈ��ǰ���
		virtual IRequestRegisterWishItems*	createRequestRegisterWishItems()	= 0;
		virtual IResponseRegisterWishItems*	createResponseRegisterWishItems()	= 0;
		virtual bool sendSync(IRequestRegisterWishItems* req, IResponseRegisterWishItems* res) = 0;
		virtual bool sendAsync(IRequestRegisterWishItems* req) = 0;
		
		// Cart & Wish Items Step 10: Remove Wish Items : ���� ������ ����
		virtual IRequestRemoveWishItems*	createRequestRemoveWishItems()	= 0;
		virtual IResponseRemoveWishItems*	createResponseRemoveWishItems()	= 0;
		virtual bool sendSync(IRequestRemoveWishItems* req, IResponseRemoveWishItems* res) = 0;
		virtual bool sendAsync(IRequestRemoveWishItems* req) = 0;
		
		// Cart & Wish Items Step 11: Remove Wish : ���� ������ �ʱ�ȭ
		virtual IRequestRemoveWish*		createRequestRemoveWish()	= 0;
		virtual IResponseRemoveWish*	createResponseRemoveWish()	= 0;
		virtual bool sendSync(IRequestRemoveWish* req, IResponseRemoveWish* res) = 0;
		virtual bool sendAsync(IRequestRemoveWish* req) = 0;
		
		// Cart & Wish Items Step 12: Wish Items Transfer Cart Items : ����īƮ�� ���� ������ �̵�
		virtual IRequestWishItemsTransferCartItems*		createRequestWishItemsTransferCartItems()	= 0;
		virtual IResponseWishItemsTransferCartItems*	createResponseWishItemsTransferCartItems()	= 0;
		virtual bool sendSync(IRequestWishItemsTransferCartItems* req, IResponseWishItemsTransferCartItems* res) = 0;
		virtual bool sendAsync(IRequestWishItemsTransferCartItems* req) = 0;
	};

	// Advanced Billing - Order : thread unsafe
	class IOrder : public IObject
	{
	public:
		IOrder(){}
		virtual ~IOrder(){}

		// Order Step 1: Shop Direct Purchase Item : �ٷα���
		virtual IRequestShopDirectPurchaseItem*		createRequestShopDirectPurchaseItem()	= 0;
		virtual IResponseShopDirectPurchaseItem*	createResponseShopDirectPurchaseItem()	= 0;
		virtual bool sendSync(IRequestShopDirectPurchaseItem* req, IResponseShopDirectPurchaseItem* res) = 0;
		virtual bool sendAsync(IRequestShopDirectPurchaseItem* req) = 0;

		// Order Step 2: Shop Direct Purchase Item by Bind Attribute : ������ �ͼ� ���¿� ���� �ٷα���
		virtual IRequestShopDirectPurchaseItemByBindAttribute*		createRequestShopDirectPurchaseItemByBindAttribute()	= 0;
		virtual IResponseShopDirectPurchaseItemByBindAttribute*		createResponseShopDirectPurchaseItemByBindAttribute()	= 0;
		virtual bool sendSync(IRequestShopDirectPurchaseItemByBindAttribute* req, IResponseShopDirectPurchaseItemByBindAttribute* res)	= 0;
		virtual bool sendAsync(IRequestShopDirectPurchaseItemByBindAttribute* req)	= 0;

		// Order Step 3: Shop Purchase Cart Items : ����īƮ����
		virtual IRequestShopPurchaseCartItems*	createRequestShopPurchaseCartItems()	= 0;
		virtual IResponseShopPurchaseCartItems*	createResponseShopPurchaseCartItems()	= 0;
		virtual bool sendSync(IRequestShopPurchaseCartItems* req, IResponseShopPurchaseCartItems* res) = 0;
		virtual bool sendAsync(IRequestShopPurchaseCartItems* req) = 0;

		// Order Step 4: Shop Direct Gift Item : �ٷμ���
		virtual IRequestShopDirectGiftItem*		createRequestShopDirectGiftItem()	= 0;
		virtual IResponseShopDirectGiftItem*	createResponseShopDirectGiftItem()	= 0;
		virtual bool sendSync(IRequestShopDirectGiftItem* req, IResponseShopDirectGiftItem* res) = 0;
		virtual bool sendAsync(IRequestShopDirectGiftItem* req) = 0;

		// Order Step 5: Shop Direct Gift Item by Bind Attribute : ������ �ͼ� ���¿� ���� �ٷμ���
		virtual IRequestShopDirectGiftItemByBindAttribute*		createRequestShopDirectGiftItemByBindAttribute()	= 0;
		virtual IResponseShopDirectGiftItemByBindAttribute*		createResponseShopDirectGiftItemByBindAttribute()	= 0;
		virtual bool sendSync(IRequestShopDirectGiftItemByBindAttribute* req, IResponseShopDirectGiftItemByBindAttribute* res)	= 0;
		virtual bool sendAsync(IRequestShopDirectGiftItemByBindAttribute* req)	= 0;

		// Order Step 6: Shop Gift Cart Items : ����īƮ����
		virtual IRequestShopGiftCartItems*	createRequestShopGiftCartItems()	= 0;
		virtual IResponseShopGiftCartItems*	createResponseShopGiftCartItems()	= 0;
		virtual bool sendSync(IRequestShopGiftCartItems* req, IResponseShopGiftCartItems* res) = 0;
		virtual bool sendAsync(IRequestShopGiftCartItems* req) = 0;

	};

	// Coupon : thread unsafe
	class ICoupon : public IObject
	{
	public:
		ICoupon(){}
		virtual ~ICoupon(){}
		
		// Coupon Step 1: Check Coupon : ���� üũ
		virtual IRequestCheckCoupon*	createRequestCheckCoupon()	= 0;
		virtual IResponseCheckCoupon*	createResponseCheckCoupon()	= 0;
		virtual bool sendSync(IRequestCheckCoupon* req, IResponseCheckCoupon* res) = 0;
		virtual bool sendAsync(IRequestCheckCoupon* req) = 0;

		// Coupon Step 2: Check Coupon by Bind Attribute : ������ �ͼ� ���¿� ���� ���� üũ
		virtual IRequestCheckCouponByBindAttribute*		createRequestCheckCouponByBindAttribute() = 0;
		virtual IResponseCheckCouponByBindAttribute*	createResponseCheckCouponByBindAttribute() = 0;
		virtual bool sendSync(IRequestCheckCouponByBindAttribute* req, IResponseCheckCouponByBindAttribute* res) = 0;
		virtual bool sendAsync(IRequestCheckCouponByBindAttribute* req) = 0;

		// Coupon Step 3: Use Coupon : ���� ���
		virtual IRequestUseCoupon*		createRequestUseCoupon()	= 0;
		virtual IResponseUseCoupon*		createResponseUseCoupon()	= 0;
		virtual bool sendSync(IRequestUseCoupon* req, IResponseUseCoupon* res) = 0;
		virtual bool sendAsync(IRequestUseCoupon* req) = 0;

		// Coupon Step 4: Use Coupon by Bind Attribute : ������ �ͼ� ���¿� ���� ���� ���
		virtual IRequestUseCouponByBindAttribute*		createRequestUseCouponByBindAttribute()	= 0;
		virtual IResponseUseCouponByBindAttribute*		createResponseUseCouponByBindAttribute() = 0;
		virtual bool sendSync(IRequestUseCouponByBindAttribute* req, IResponseUseCouponByBindAttribute* res) = 0;
		virtual bool sendAsync(IRequestUseCouponByBindAttribute* req) = 0;

	};

///////////////////////////////////////////////////////////////////////////////////////////////////
// IAsyncReciver
//	��� Requeset, Response DTO �� ����� ������ release() ȣ���� �ϼž� �޸� ������ �����ϴ�.

	class IAsyncReceiverAuth
	{
	public:
		IAsyncReceiverAuth(){}
		virtual ~IAsyncReceiverAuth(){}

		// Authentication & Authorization Step 1: Game Login : ���� �α���
		virtual void onGameLogin(fcsa::IResponseGameLogin* res)	{ res->release(); }
		// Authentication & Authorization Step 2: Game Logout : ���� �α׾ƿ�
		virtual void onGameLogout(fcsa::IResponseGameLogout* res) { res->release(); }
		// Authentication & Authorization Step 3: Premium Service Expired Callback : �����̾� ���� �Ⱓ ����
		virtual void onPremiumServiceExpiredCallback(fcsa::IResponsePremiumServiceExpiredCallback* res)	{ res->release(); }
		// Authentication & Authorization Step 4: Force User Logout Callback : ���� �α׾ƿ�
		virtual void onForceUserLogoutCallback(fcsa::IResponseForceUserLogoutCallback* res)	{ res->release(); }
		// Authentication & Authorization Step 5: Request Authentication Key : ����Ű ��û
		virtual void onAuthenticationKey(fcsa::IResponseAuthenticationKey* res)	{ res->release(); }
		// Authentication & Authorization Step 6: Validate Authentication Key : ����Ű ��ȿ�� �˻�
		virtual void onValidateAuthenticationKey(fcsa::IResponseValidateAuthenticationKey* res)	{ res->release(); }
		// Authentication & Authorization Step 7: Validate Authentication Key with Extension : ����Ű ��ȿ�� �˻�
		virtual void onValidateAuthenticationKeyWithExtension(fcsa::IResponseValidateAuthenticationKeyWithExtension* res) { res->release(); }
		// Authentication & Authorization Step 8: Validate Authentication Key for Publisher : ����Ű ��ȿ�� �˻�
		virtual void onValidateAuthenticationKeyForPublisher(fcsa::IResponseValidateAuthenticationKeyForPublisher* res)	{ res->release(); }
		// Authentication & Authorization Step 9: Validate Authentication Key with Parent Safe : �θ� �Ƚ� ���� ����Ű ��ȿ�� �˻�
		virtual void onValidateAuthenticationKeyWithParentSafe(fcsa::IResponseValidateAuthenticationKeyWithParentSafe* res) { res->release(); }
		// Authentication & Authorization Step 10: Validate Authentication Key for R2 : ���� R2 �� ����Ű ��ȿ�� �˻�
		virtual void onValidateAuthenticationKeyForR2(fcsa::IResponseValidateAuthenticationKeyForR2* res) { res->release(); }
		// Authentication & Authorization Step 11: Validate Authentication Key with User Info : ����Ű ��ȿ�� �˻� (���� ���� Ȯ��)
		virtual void onValidateAuthenticationKeyWithUserInfo(fcsa::IResponseValidateAuthenticationKeyWithUserInfo* res) { res->release(); }
		// Authentication & Authorization Step 12: Account Login : ���� �α���
		virtual void onAccountLogin(fcsa::IResponseAccountLogin* res) { res->release(); }
		// Authentication & Authorization Step 13: Account Logout : ���� �α׾ƿ�
		virtual void onAccountLogout(fcsa::IResponseAccountLogout* res) { res->release(); }
		// Authentication & Authorization Step 14: Set Account State : ������ ������ �α���/�α׾ƿ� ���� ��ȣ, IP, �ð�, �����α��� Ƚ�� ������Ʈ
		virtual void onSetAccountState(fcsa::IResponseSetAccountState* res) { res->release(); }
		// Authentication & Authorization Step 15: Get PC Room Guid : IP�� PC�� ������ȣ ��ȯ
		virtual void onGetPCRoomGuid(fcsa::IResponseGetPCRoomGuid* res) { res->release(); }
		// Authentication & Authorization Step 16: Check Phone Auth User : ��ȭ���� ���԰��� ���� Ȯ��
		virtual void onCheckPhoneAuthUser(fcsa::IResponseCheckPhoneAuthUser* res) { res->release(); }
		// Authentication & Authorization Step 17: Get User Info : ������ȣ�� ����� ���� Ȯ��
		virtual void onGetUserInfo(fcsa::IResponseGetUserInfo* res) { res->release(); }
		// Authentication & Authorization Step 18: Get User Info With Extension : ������ȣ�� ����� ���� Ȯ��
		virtual void onGetUserInfoWithExtension(fcsa::IResponseGetUserInfoWithExtension* res) { res->release(); }
	};
	class IAsyncReceiverBasicBilling
	{
	public:
		IAsyncReceiverBasicBilling(){}
		virtual ~IAsyncReceiverBasicBilling(){}

		// Basic Billing Step 1: Check Balance : �ܾ���ȸ Response
		virtual void onCheckBalance(fcsa::IResponseCheckBalance* res) { res->release(); }
		// Basic Billing Step 2: Item Purchase : ������ ���� Response
		virtual void onItemPurchase(fcsa::IResponseItemPurchase* res) { res->release(); }
		// Basic Billing Step 3: Item Gift : ��ǰ ���� Response
		virtual void onItemGift(fcsa::IResponseItemGift* res) { res->release(); }
		// Basic Billing Step 4: Check Purchase : ���� Ȯ�� Response
		virtual void onCheckPurchase(fcsa::IResponseCheckPurchase* res) { res->release(); }
		// Basic Billing Step 5: Cancel Purchase : ���� ��� Response
		virtual void onCancelPurchase(fcsa::IResponseCancelPurchase* res) { res->release(); }
		// Basic Billing Step 6: Cancel Purchase by Order Id : �ֹ���ȣ�� �̿��ؼ� ��ü ���� ��� Response
		virtual void onCancelPurchaseByOrderId(fcsa::IResponseCancelPurchaseByOrderId* res) { res->release(); }
		// Basic Billing Step 7: Confirm Purchase by Order Id : �ֹ���ȣ�� �̿��ؼ� ��ü ���� ���� Response
		virtual void onConfirmPurchaseByOrderId(fcsa::IResponseConfirmPurchaseByOrderId* res) { res->release(); }
		// Basic Billing Step 8: Purchase List : ���ų��� ��ȸ Response
		virtual void onPurchaseList(fcsa::IResponsePurchaseList* res) { res->release(); }
		// Basic Billing Step 9: Exchange WCoin : WCoin�� ���� ������ ���Ǵ� ����Ʈ�� ��ȯ
		virtual void onExchangeWCoin(fcsa::IResponseExchangeWCoin* res) { res->release(); }
	};

	class IAsyncReceiverWShopBilling
	{
	public:
		IAsyncReceiverWShopBilling(){}
		virtual ~IAsyncReceiverWShopBilling(){}

		// WShop Billing Step 1 : WShop Check Balance : �ܾ���ȸ
		virtual void onWShopCheckBalance(fcsa::IResponseWShopCheckBalance* res) { res->release(); }
		// WShop Billing Step 2 : WShopPurchase : �� ������ ����
		virtual void onWShopPurchase(fcsa::IResponseWShopPurchase* res) { res->release(); }
		// WShop Billing Step 3 : WShopCheckPurchase : �� ������ ���� Ȯ��
		virtual void onWShopCheckPurchase(fcsa::IResponseWShopCheckPurchase* res) { res->release(); }
		// WShop Billing Step 4 : WShopCancelPurchase : �� ������ ���� ���
		virtual void onWShopCancelPurchase(fcsa::IResponseWShopCancelPurchase* res) { res->release(); }
		// WShop Billing Step 5 : WShopConfirmPurchase : �� ������ ���� ����
		virtual void onWShopConfirmPurchase(fcsa::IResponseWShopConfirmPurchase* res) { res->release(); }
		// WShop Billing Step 6 : WShopGift : �� ������ ����
		virtual void onWShopGift(fcsa::IResponseWShopGift* res) { res->release(); }
		// WShop Billing Step 7 : WShopCheckGift : ���� �� Ȯ��
		virtual void onWShopCheckGift(fcsa::IResponseWShopCheckGift* res) { res->release(); }
		// WShop Billing Step 8 : WShopCancelGift : ���� �� ���
		virtual void onWShopCancelGift(fcsa::IResponseWShopCancelGift* res) { res->release(); }
		// WShop Billing Step 9 : WShopConfirmGift : ��� ���� �� ����
		virtual void onWShopConfirmGift(fcsa::IResponseWShopConfirmGift* res) { res->release(); }
		// WShop Billing Step 10 : WShopGetVersion : �� ���� ���� ��ȸ
		virtual void onWShopGetVersion(fcsa::IResponseWShopGetVersion* res) { res->release(); }
	};

	class IAsyncReceiverWShopInventory
	{
	public:
		IAsyncReceiverWShopInventory(){}
		virtual ~IAsyncReceiverWShopInventory(){}

		// WShop Inventory Step 1 : WShop Inquiry New Arrival : ���� �������� ���� ���� �κ��丮 ������ ��ȸ
		virtual void onWShopInquiryNewArrival(fcsa::IResponseWShopInquiryNewArrival* res) { res->release(); }
		// WShop Inventory Step 2 : WShop Inquiry Inventory : �κ��丮 ��ȸ
		virtual void onWShopInquiryInventory(fcsa::IResponseWShopInquiryInventory* res) { res->release(); }
		// WShop Inventory Step 3 : WShop Pick Up : �κ��丮 ����
		virtual void onWShopPickUp(fcsa::IResponseWShopPickUp* res) { res->release(); }
		// WShop Inventory Step 4 : WShop Check Pick Up : �κ��丮 ���� �� Ȯ��
		virtual void onWShopCheckPickUp(fcsa::IResponseWShopCheckPickUp* res) { res->release(); }
		// WShop Inventory Step 5 : WShop Cancel Pick Up : �κ��丮���ɰ����
		virtual void onWShopCancelPickUp(fcsa::IResponseWShopCancelPickUp* res) { res->release(); }
		// WShop Inventory Step 6 : WShop Confirm Pick Up : �κ��丮���ɰǽ���
		virtual void onWShopConfirmPickUp(fcsa::IResponseWShopConfirmPickUp* res) { res->release(); }
	};

	class IAsyncReceiverJewel
	{
	public:
		IAsyncReceiverJewel(){}
		virtual ~IAsyncReceiverJewel(){}

		// Jewel Step 1  : Charge Jewel : ���������û
		virtual void onChargeJewel(fcsa::IResponseChargeJewel* res) { res->release(); }
		// Jewel Step 2  : Check Jewel Charge : ���������Ȯ��
		virtual void onCheckJewelCharge(fcsa::IResponseCheckJewelCharge* res) { res->release(); }
		// Jewel Step 3  : Cancel Jewel Charge : ������������
		virtual void onCancelJewelCharge(fcsa::IResponseCancelJewelCharge* res) { res->release(); }
		// Jewel Step 4  : Confirm Jewel Charge : ��������ǽ���
		virtual void onConfirmJewelCharge(fcsa::IResponseConfirmJewelCharge* res) { res->release(); }
		// Jewel Step 5  : Purchase Jewel Item : ������
		virtual void onPurchaseJewelItem(fcsa::IResponsePurchaseJewelItem* res) { res->release(); }
		// Jewel Step 6  : Check Purchase Jewel : ��������Ȯ��
		virtual void onCheckPurchaseJewel(fcsa::IResponseCheckPurchaseJewel* res) { res->release(); }
		// Jewel Step 7  : Cancel Jewel Purchase : �����������
		virtual void onCancelJewelPurchase(fcsa::IResponseCancelJewelPurchase* res) { res->release(); }
		// Jewel Step 8  : Confirm Jewel Purchase : �������ǽ���
		virtual void onConfirmJewelPurchase(fcsa::IResponseConfirmJewelPurchase* res) { res->release(); }
		// Jewel Step 9  : Trade Jewel : �������ŷ�
		virtual void onTradeJewel(fcsa::IResponseTradeJewel* res) { res->release(); }
		// Jewel Step 10 : Check Trade Jewel : �������ŷ���Ȯ�� 
		virtual void onCheckTradeJewel(fcsa::IResponseCheckTradeJewel* res) { res->release(); }
		// Jewel Step 11 : Cancel Jewel Trade : �������ŷ������
		virtual void onCancelJewelTrade(fcsa::IResponseCancelJewelTrade* res) { res->release(); }
		// Jewel Step 12 : Confirm Jewel Trade : ��� ����� �ŷ��� ����
		virtual void onConfirmJewelTrade(fcsa::IResponseConfirmJewelTrade* res) { res->release(); }
		// Jewel Step 13 : Pick Up Trade Jewel : ��� ����� �Ǹűݾ� ����(�Ǹ���)
		virtual void onPickUpTradeJewel(fcsa::IResponsePickUpTradeJewel* res) { res->release(); }
		// Jewel Step 14 : Check Trade Jewel Pick Up : ����� �Ǹűݾ� ���ɰ� Ȯ��
		virtual void onCheckTradeJewelPickUp(fcsa::IResponseCheckTradeJewelPickUp* res) { res->release(); }
		// Jewel Step 15 : Cancel Trade Jewel Pick Up : ����� �Ǹűݾ� ���ɰ� ���
		virtual void onCancelTradeJewelPickUp(fcsa::IResponseCancelTradeJewelPickUp* res) { res->release(); }
		// Jewel Step 16 : Confirm Trade Jewel Pick Up : ����� �Ǹűݾ� ���ɰ� ����
		virtual void onConfirmTradeJewelPickUp(fcsa::IResponseConfirmTradeJewelPickUp* res) { res->release(); }
	};

	class IAsyncReceiverCashInventory
	{
	public:
		IAsyncReceiverCashInventory(){}
		virtual ~IAsyncReceiverCashInventory(){}

		// Cash Inventory Step 1: Inquiry Cash Inventory - ĳ���κ��丮��ȸ Response
		virtual void onInquiryCashInventory(IResponseInquiryCashInventory* res) {res->release();}
		// Cash Inventory Step 2: Inquiry Cash Inventory by Bind Attribute - ������ �ͼ� ���¿� ���� ĳ���κ��丮��ȸ
		virtual void onInquiryCashInventoryByBindAttribute(IResponseInquiryCashInventoryByBindAttribute* res) {res->release();}
		// Cash Inventory Step 3: Pickup Cash Inventory Item - ĳ���κ��丮���� Response
		virtual void onPickupCashInventoryItem(IResponsePickupCashInventoryItem* res) {res->release();}
		// Cash Inventory Step 4: Pickup Cash Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ĳ���κ��丮����
		virtual void onPickupCashInventoryItemByBindAttribute(IResponsePickupCashInventoryItemByBindAttribute* res) {res->release();}
		// Cash Inventory Step 5: Cancel Pickup Cash Inventory Item - ĳ���κ��丮������� Response
		virtual void onCancelCashInventoryItem(IResponseCancelCashInventoryItem* res) {res->release();}
		// Cash Inventory Step 6: Cancel Pickup Cash Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ĳ���κ��丮�������
		virtual void onCancelCashInventoryItemByBindAttribute(IResponseCancelCashInventoryItemByBindAttribute* res) {res->release();}
		// Cash Inventory Step 7: Pickup Cash Sub Inventory Item - ����ĳ���κ��丮���� Response
		virtual void onPickupCashSubInventoryItem(IResponsePickupCashSubInventoryItem* res) {res->release();}
		// Cash Inventory Step 8: Pickup Cash Sub Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ����ĳ���κ��丮����
		virtual void onPickupCashSubInventoryItemByBindAttribute(IResponsePickupCashSubInventoryItemByBindAttribute* res) {res->release();}
		// Cash Inventory Step 9: Cancel Cash Sub Inventory Item - ����ĳ���κ��丮��� Response
		virtual void onCancelCashSubInventoryItem(IResponseCancelCashSubInventoryItem* res) {res->release();}
		// Cash Inventory Step 10: Cancel Cash Sub Inventory Item by Bind Attribute - ������ �ͼ� ���¿� ���� ����ĳ���κ��丮���
		virtual void onCancelCashSubInventoryItemByBindAttribute(IResponseCancelCashSubInventoryItemByBindAttribute* res) { res->release(); }
		// Cash Inventory Step 11: Inquiry Pickup Standby Cash Purchase No - ���ӿ��� ���� ������ ������ ���Ź�ȣ ����Ʈ ��ȸ
		virtual void onInquiryPickupStandbyCashPurchaseNo(IResponseInquiryPickupStandbyCashPurchaseNo* res) { res->release(); }
		// Cash Inventory Step 12: Pickup Standby Cash Inventory - ���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �����·� ��ȯ
		virtual void onPickupStandbyCashInventory(IResponsePickupStandbyCashInventory* res) { res->release(); }
		// Cash Inventory Step 13: Complete Pickup Standby Cash Inventory - ���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �Ϸ���·� ��ȯ
		virtual void onCompletePickupStandbyCashInventory(IResponseCompletePickupStandbyCashInventory* res) { res->release(); }
		// Cash Inventory Step 14: Cancel Pickup Standby Cash Inventory - ���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �����¿��� ���
		virtual void onCancelPickupStandbyCashInventory(IResponseCancelPickupStandbyCashInventory* res) { res->release(); }
		// Cash Inventory Step 15: Use Storage - IBS ������ ��ǰ ���
		virtual void onUseStorage(IResponseUseStorage* res) { res->release(); }
		// Cash INventory Step 16: Rollback Use Storage - IBS ������ ��� �ѹ�
		virtual void onRollbackUseStorage(IResponseRollbackUseStorage* res) { res->release(); }
	};
	class IAsyncReceiverStatus
	{
		public:
		IAsyncReceiverStatus(){}
		virtual ~IAsyncReceiverStatus(){}

		// W Shop ������ ���� ������Ʈ �˸� callback response : W Shop ��ǰ������ ���ŵ� ��� ������ ���� �޴� �ݹ� �̺�Ʈ
		virtual void onConflictProductVersion() {}
	};
	class IAsyncReceiverInquiryOData
	{
	public:
		IAsyncReceiverInquiryOData(){}
		virtual ~IAsyncReceiverInquiryOData(){}

		// ��ǰ ���� ���� callback response : ��ǰ������ ���ŵ� ��� ������ ���� �޴� �ݹ� �̺�Ʈ
		virtual void onConflictProductVersion() {}
		// Inquiry OData Step 1: Inquiry Service Metadata : Metadata ��ȸ Response
		virtual void onInquiryServiceMetadata(IResponseInquiryServiceMetadata* res) {res->release();}
		// Inquiry OData Step 2: Inquiry OData Service: OData ��ȸ Response
		virtual void onInquiryODataService(IResponseInquiryODataService* res) {res->release();}
	};
	class IAsyncReceiverCartAndWishItems
	{
	public:
		IAsyncReceiverCartAndWishItems(){}
		virtual ~IAsyncReceiverCartAndWishItems(){}

		// Cart & Wish Items Step 1: Inquiry Cart Items : ����īƮ��ȸ Response
		virtual void onInquiryCartItems(IResponseInquiryCartItems* res) {res->release();}
		// Cart & Wish Items Step 2: Register Cart Items : ����īƮ��ǰ��� Response
		virtual void onRegisterCartItems(IResponseRegisterCartItems* res) {res->release();}
		// Cart & Wish Items Step 3: Modify Cart Items Quantity : ����īƮ�����ۺ��� Response
		virtual void onModifyCartItemsQuantity(IResponseModifyCartItemsQuantity* res) {res->release();}
		// Cart & Wish Items Step 4: Modify Cart Items Attribute : ����īƮ�����ۺ��� Response
		virtual void onModifyCartItemsAttribute(IResponseModifyCartItemsAttribute* res) {res->release();}
		// Cart & Wish Items Step 5: Remove Cart Items : ����īƮ�����ۻ��� Response
		virtual void onRemoveCartItems(IResponseRemoveCartItems* res) {res->release();}
		// Cart & Wish Items Step 6: Remove Cart : ����īƮ�ʱ�ȭ Response
		virtual void onRemoveCart(IResponseRemoveCart* res) {res->release();}
		// Cart & Wish Items Step 7: Cart Items Transfer Wish Items : ���þ��������� ����īƮ ������ �̵� Response
		virtual void onCartItemsTransferWishItems(IResponseCartItemsTransferWishItems* res) {res->release();}
		// Cart & Wish Items Step 8: Inquiry Wish Items : ���þ�������ȸ Response
		virtual void onInquiryWishItems(IResponseInquiryWishItems* res) {res->release();}
		// Cart & Wish Items Step 9: Register Wish Items : Wish ����Ʈ��ǰ��� Response
		virtual void onRegisterWishItems(IResponseRegisterWishItems* res) {res->release();}
		// Cart & Wish Items Step 10: Remove Wish Items : ���� ������ ���� Response
		virtual void onRemoveWishItems(IResponseRemoveWishItems* res) {res->release();}
		// Cart & Wish Items Step 11: Remove Wish : ���� ������ �ʱ�ȭ Response
		virtual void onRemoveWish(IResponseRemoveWish* res) {res->release();}
		// Cart & Wish Items Step 12: Wish Items Transfer Cart Items : ����īƮ�� ���� ������ �̵� Response
		virtual void onWishItemsTransferCartItems(IResponseWishItemsTransferCartItems* res) {res->release();}
	};
	class IAsyncReceiverOrder
	{
	public:
		IAsyncReceiverOrder(){}
		virtual ~IAsyncReceiverOrder(){}

		// Order Step 1: Shop Direct Purchase Item : �ٷα��� Response
		virtual void onShopDirectPurchaseItem(IResponseShopDirectPurchaseItem* res) {res->release();}
		// Order Step 2: Shop Direct Purchase Item by Bind Attribute : ������ �ͼ� ���¿� ���� �ٷα���
		virtual void onShopDirectPurchaseItemByBindAttribute(IResponseShopDirectPurchaseItemByBindAttribute* res) { res->release(); }
		// Order Step 3: Shop Purchase Cart Items : ����īƮ���� Response
		virtual void onShopPurchaseCartItems(IResponseShopPurchaseCartItems* res) {res->release();}
		// Order Step 4: Shop Direct Gift Item : �ٷμ��� Response
		virtual void onShopDirectGiftItem(IResponseShopDirectGiftItem* res) {res->release();}
		// Order Step 5: Shop Direct Gift Item by Bind Attribute : ������ �ͼ� ���¿� ���� �ٷμ���
		virtual void onShopDirectGiftItemByBindAttribute(IResponseShopDirectGiftItemByBindAttribute* res) { res->release(); }
		// Order Step 6: Shop Gift Cart Items : ����īƮ���� Response
		virtual void onShopGiftCartItems(IResponseShopGiftCartItems* res) {res->release();}
	};
	class IAsyncReceiverCoupon
	{
	public:
		IAsyncReceiverCoupon(){}
		virtual ~IAsyncReceiverCoupon(){}
		
		// Coupon Step 1: Check Coupon : ���� üũ Response
		virtual void onCheckCoupon(IResponseCheckCoupon* res) {res->release();}
		// Coupon Step 2: Check Coupon by Bind Attribute : ������ �ͼ� ���¿� ���� ���� üũ
		virtual void onCheckCouponByBindAttribute(IResponseCheckCouponByBindAttribute* res) { res->release(); }
		// Coupon Step 3: Use Coupon : ���� ��� Response
		virtual void onUseCoupon(IResponseUseCoupon* res) {res->release();}
		// Coupon Step 4: Use Coupon by Bind Attribute : ������ �ͼ� ���¿� ���� ���� ���
		virtual void onUseCouponByBindAttribute(IResponseUseCouponByBindAttribute* res) { res->release(); }
	};

} // namespace

#endif