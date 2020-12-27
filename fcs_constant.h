#ifndef FCSADAPTER_INTERFACE_CONSTANT_H_
#define FCSADAPTER_INTERFACE_CONSTANT_H_

namespace fcsa {

	/////////////////////////////////////////////////////////////////////////////////////
	// Reserved Character : ��� ��Ŷ�� ù��° BYTE�� ���� ����
	const BYTE kReservedCharacter								 = 0xFF;

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 1 Packet Types
	// Common
	const BYTE kPacketType_Initialize									= 0x01; //Front Channel Service�� ����     
	const BYTE kPacketType_KeepAlive									= 0x02; //������� Ȯ��                    
	// Authentication & Authorization
	const BYTE kPacketType_GameLogin									= 0x11; //���ӷα���                       
	const BYTE kPacketType_GameLogout									= 0x12; //���ӷα׾ƿ�                     
	const BYTE kPacketType_PremiumServiceExpiredCallback				= 0x13; //�����̾� ���� �Ⱓ ���� �뺸   
	const BYTE kPacketType_ForceUserLogoutCallback						= 0x14; //����� ���� �α׾ƿ�             
	const BYTE kPacketType_RequestAuthenticationKey						= 0x21; //����Ű ��û                      
	const BYTE kPacketType_ValidateAuthenticationKey					= 0x22; //����Ű ��ȿ�� Ȯ��               
	const BYTE kPacketType_ValidateAuthenticationKeyWithExtension		= 0x23; //����Ű ��ȿ�� Ȯ��               
	const BYTE kPacketType_ValidateAuthenticationKeyForPublisher		= 0x24; //����Ű ��ȿ�� Ȯ��
	const BYTE kPacketType_ValidateAuthenticationKeyWithParentSafe		= 0x25;	//�θ� �Ƚ� ���� ����Ű ��ȿ�� �˻�
	const BYTE kPacketType_ValidateAuthenticationKeyForR2				= 0x26; //���� R2 �� ����Ű ��ȿ�� �˻�
	const BYTE kPacketType_ValidateAuthenticationKeyWithUserInfo		= 0x27; //����Ű ��ȿ�� Ȯ��(���� ���� ��ȸ)
	const BYTE kPacketType_AccountLogin									= 0x31; //WEBZEN Account Login
	const BYTE kPacketType_AccountLogout								= 0x32; //WEBZEN Account Logout
	const BYTE kPacketType_SetAccountState								= 0x33; //������ ������ �α���/�α׾ƿ� ���� ������Ʈ
	const BYTE kPacketType_GetPCRoomGuid								= 0x34; //IP�� PC�� ������ȣ ��ȯ
	const BYTE kPacketType_CheckPhoneAuthUser							= 0x35; //��ȭ���� ���԰��� ���� Ȯ��
	const BYTE kPacketType_GetUserInfo									= 0x36; //������ȣ�� ����� ���� Ȯ��
	const BYTE kPacketType_GetUserInfoWithExtension						= 0x37; //������ȣ�� ����� ���� Ȯ��
	const BYTE kPacketType_ActivateFlatRatePaymentProduct				= 0x41; //���׻�ǰ Ȱ��ȭ                  
	const BYTE kPacketType_DeactivateFlatRatePaymentProduct				= 0x42; //���׻�ǰ ��Ȱ��ȭ                
	// Basic Billing
	const BYTE kPacketType_CheckBalance									= 0x51; //�ܾ���ȸ                         
	const BYTE kPacketType_ItemPurchase									= 0x61; //���� ������ ����                 
	const BYTE kPacketType_ItemGift										= 0x62; //���� ������ ����                 
	const BYTE kPacketType_CheckPurchase								= 0x63; //����Ȯ��                         
	const BYTE kPacketType_CancelPurchase								= 0x64; //�������                         
	const BYTE kPacketType_CancelPurchaseByOrderId						= 0x65; //�ֹ���ȣ�� �̿��ؼ� ��ü �������
	const BYTE kPacketType_ConfirmPurchaseByOrderId						= 0x66; //�ֹ���ȣ�� �̿��ؼ� ��ü ���Ž���
	const BYTE kPacketType_PurchaseList									= 0x71; //���ų�����ȸ
	const BYTE kPacketType_ExchangeWCoin								= 0x72; //WCoin�� ���� ������ ���Ǵ� ����Ʈ�� ��ȯ
	// WShop Billing
	const BYTE kPacketType_WShopCheckBalance                            = 0x90; //�ܾ���ȸ
	const BYTE kPacketType_WShopPurchase                                = 0x91; //�� ������ ����
	const BYTE kPacketType_WShopCheckPurchase                           = 0x92; //�� ������ ���� Ȯ��
	const BYTE kPacketType_WShopCancelPurchase                          = 0x93; //�� ������ ���� ���
	const BYTE kPacketType_WShopConfirmPurchase                         = 0x94; //�� ������ ���� ����
	const BYTE kPacketType_WShopGift                                    = 0x95; //�� ������ ����
	const BYTE kPacketType_WShopCheckGift                               = 0x96; //���� �� Ȯ��
	const BYTE kPacketType_WShopCancelGift                              = 0x97; //���� �� ���
	const BYTE kPacketType_WShopConfirmGift                             = 0x98; //��� ���� �� ����
	const BYTE kPacketType_WShopGetVersion                              = 0x99; //�� ���� ���� ��ȸ
	// WShop Inventory
	const BYTE kPacketType_WShopInquiryNewArrival                       = 0x9A; //���� �������� ���� ���� �κ��丮 ������ ��ȸ
	const BYTE kPacketType_WShopInquiryInventory                        = 0x9B; //�κ��丮 ��ȸ	
	const BYTE kPacketType_WShopPickUp                                  = 0x9C; //�κ��丮 ����
	const BYTE kPacketType_WShopCheckPickUp                             = 0x9D; //�κ��丮 ���� �� Ȯ��
	const BYTE kPacketType_WShopCancelPickUp                            = 0x9E; //�κ��丮���ɰ����
	const BYTE kPacketType_WShopConfirmPickUp                           = 0x9F; //�κ��丮���ɰǽ���
	//Jewel
	const BYTE kPacketType_ChargeJewel                                  = 0xB0; //���������û
	const BYTE kPacketType_CheckJewelCharge                             = 0xB1; //���������Ȯ��
	const BYTE kPacketType_CancelJewelCharge                            = 0xB2; //������������
	const BYTE kPacketType_ConfirmJewelCharge                           = 0xB3; //��������ǽ���
	const BYTE kPacketType_PurchaseJewelItem                            = 0xB4; //������
	const BYTE kPacketType_CheckPurchaseJewel                           = 0xB5; //��������Ȯ��
	const BYTE kPacketType_CancelJewelPurchase                          = 0xB6; //�����������
	const BYTE kPacketType_ConfirmJewelPurchase                         = 0xB7; //�������ǽ���
	const BYTE kPacketType_TradeJewel                                   = 0xB8; //�������ŷ�
	const BYTE kPacketType_CheckTradeJewel                              = 0xB9; //�������ŷ���Ȯ��
	const BYTE kPacketType_CancelJewelTrade                             = 0xBA; //�������ŷ������
	const BYTE kPacketType_ConfirmJewelTrade                            = 0xBB; //��� ����� �ŷ��� ����
	const BYTE kPacketType_PickUpTradeJewel								= 0xBC; // ��� ����� �Ǹűݾ� ����(�Ǹ���)
	const BYTE kPacketType_CheckTradeJewelPickUp						= 0xBD; // ����� �Ǹűݾ� ���ɰ� Ȯ��
	const BYTE kPacketType_CancelTradeJewelPickUp						= 0xBE; // ����� �Ǹűݾ� ���ɰ� ���
	const BYTE kPacketType_ConfirmTradeJewelPickUp						= 0xBF; // ����� �Ǹűݾ� ���ɰ� ����
	
	// Advanced Billing - Cash Inventory
	const BYTE kPacketType_InquiryCashInventory							= 0x69; //ĳ���κ��丮��ȸ
	const BYTE kPacketType_InquiryCashInventoryByBindAttribute			= 0x81; //������ �ͼ� ���¿� ���� ĳ���κ��丮��ȸ
	const BYTE kPacketType_PickupCashInventoryItem						= 0x6B; //ĳ���κ��丮����
	const BYTE kPacketType_PickupCashInventoryItemByBindAttribute		= 0x82; //������ �ͼ� ���¿� ���� ĳ���κ��丮����
	const BYTE kPacketType_CancelCashInventoryItem						= 0x6C; //ĳ���κ��丮����
	const BYTE kPacketType_CancelCashInventoryItemByBindAttribute		= 0x83; //������ �ͼ� ���¿� ���� ĳ���κ��丮����
	const BYTE kPacketType_PickupCashSubInventoryItem					= 0x6D; //����ĳ���κ��丮����
	const BYTE kPacketType_PickupCashSubInventoryItemByBindAttribute	= 0x84; //������ �ͼ� ���¿� ���� ����ĳ���κ��丮����
	const BYTE kPacketType_CancelCashSubInventoryItem					= 0x6E; //����ĳ���κ��丮���
	const BYTE kPacketType_CancelCashSubInventoryItemByBindAttribute	= 0x85; //������ �ͼ� ���¿� ���� ����ĳ���κ��丮���
	const BYTE kPacketType_InquiryPickupStandbyCashPurchaseNo			= 0x86;	//���ӿ��� ���ɰ����� ������ ���Ź�ȣ ����Ʈ ��ȸ
	const BYTE kPacketType_PickupStandbyCashInventory					= 0x87;	//���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �����·� ��ȯ
	const BYTE kPacketType_CompletePickupStandbyCashInventory			= 0x8C;	//���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �Ϸ���·� ��ȯ
	const BYTE kPacketType_CancelPickupStandbyCashInventory				= 0x8D;	//���� ��ȣ�� �ش��ϴ� �������� ���� �� ���� �����¿��� ���
	const BYTE kPacketType_UseStorage									= 0x8E; //IBS ������ ��ǰ ���
	const BYTE kPacketType_RollbackUseStorage							= 0x8F; //IBS ������ ��� �ѹ�
	// Advanced Billing - Inquiry OData
	const BYTE kPacketType_InquiryServiceMetadata						= 0x74; //���񽺸�Ÿ����Ÿ��ȸ
	const BYTE kPacketType_InquiryODataService							= 0x75; //OData������ȸ
	// Advanced Billing - Cart & Wish Items
	const BYTE kPacketType_InquiryCartItems								= 0xA1; //����īƮ��������ȸ
	const BYTE kPacketType_RegisterCartItems							= 0xA2; //����īƮ�����۵��
	const BYTE kPacketType_ModifyCartItemsQuantity						= 0xA3; //����īƮ�����ۼ�������
	const BYTE kPacketType_ModifyCartItemsAttribute						= 0xA4; //����īƮ�����ۼӼ�����
	const BYTE kPacketType_RemoveCartItems								= 0xA5; //����īƮ�����ۻ���
	const BYTE kPacketType_RemoveCart									= 0xA6; //����īƮ��ü�����ۻ���
	const BYTE kPacketType_CartItemsTransferWishItems					= 0xA7; //���þ��������μ���īƮ�������̵�
	const BYTE kPacketType_InquiryWishItems								= 0xAB; //���þ�������ȸ
	const BYTE kPacketType_RegisterWishItems							= 0xAC; //���þ����۵��
	const BYTE kPacketType_RemoveWishItems								= 0xAD; //���þ����ۻ���
	const BYTE kPacketType_RemoveWish									= 0xAE; //���þ�������ü����
	const BYTE kPacketType_WishItemsTransferCartItems					= 0xAF; //����īƮ�������������þ������̵�
	// Advanced Billing - Order
	const BYTE kPacketType_ShopDirectPurchaseItem						= 0xC9; //�ٷα���
	const BYTE kPacketType_ShopDirectPurchaseItemByBindAttribute		= 0x88; //������ �ͼ� ���¿� ���� �ٷα���
	const BYTE kPacketType_ShopPurchaseCartItems						= 0xCA; //����īƮ�����۱���
	const BYTE kPacketType_ShopDirectGiftItem							= 0xCB; //�ٷμ����ϱ�
	const BYTE kPacketType_ShopDirectGiftItemByBindAttribute			= 0x89; //������ �ͼ� ���¿� ���� �ٷμ����ϱ�
	const BYTE kPacketType_ShopGiftCartItems							= 0xCC; //����īƮ�����ۼ���
	// Advanced Billing - Coupon									
	const BYTE kPacketType_CheckCoupon									= 0xDD; //������ȸ
	const BYTE kPacketType_CheckCouponByBindAttribute					= 0x8A; //������ �ͼ� ���¿� ���� ������ȸ
	const BYTE kPacketType_UseCoupon									= 0xDE; //�������
	const BYTE kPacketType_UseCouponByBindAttribute						= 0x8B; //������ �ͼ� ���¿� ���� �������


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 2 Result Codes
	//	�ý��۸޽�����Ģ
	//		system			: no rule
	//		Common			: 900XX
	//		Account			: 901XX
	//		Authorization	: 902XX
	//		Policy			: 903XX
	//		Portal			: 904XX
	//		EM				: 905XX
	//		CS				: 906XX
	//		Billing			: 907XX
	//		Coupon			: 908XX
	//		Itemshop		: 909XX
	//		Banner			: 910XX
	//		Linked			: 911XX
	//		Sync			: 912XX
	const INT32 kRCSuccess			= 1;				//����
	const INT32 kRCFailure			= 2;				//����
	const INT32 kRCException		= 3;				//����
	const INT32 kRCNoResult			= 4;				//(2-Phase Commit) ����, ����, �Ⱦ�, ������ ���� Ʈ����� ��ȸ �� ��� ����
	const INT32 kRCFailureTransactionalOperation = 5;	//(2-Phase Commit) ����, ����, �Ⱦ�, ������ ���� ���� �� ��ҿ� ���� Ʈ����� ���� ���� ��
	const INT32 kRCFCSAdapterError	= 9;	 //FCS Adapter Error

	const INT32 kRC90001			= 90001; //Parameter����
	const INT32 kRC90002			= 90002; //�ش緹�ڵ����
	const INT32 kRC90003			= 90003; //�̷µ�Ͽ���
	const INT32 kRC90004			= 90004; //�ߺ���Ͽ���
	const INT32 kRC90005			= 90005; //�����ѵ����Ͱ��߸��Ǿ����ϴ�.
	const INT32 kRC90006			= 90006; //��ȿ��������1��ī�װ���
	const INT32 kRC90007			= 90007; //��ȿ��������2��ī�װ���
	const INT32 kRC90008			= 90008; //���Ұ������
	const INT32 kRC90009			= 90009; //��Ģ�� �ϰ���� ����
	const INT32 kRC90010			= 90010; //��ȿ���� ���� ���°�

	const INT32 kRC90101			= 90101; //Userid�ߺ�����
	const INT32 kRC90102			= 90102; //Email�ߺ�����
	const INT32 kRC90103			= 90103; //����ڻ��º������
	const INT32 kRC90104			= 90104; //���������������
	const INT32 kRC90105			= 90105; //����ڵ����;���
	const INT32 kRC90106			= 90106; //��й�ȣȮ�ο���
	const INT32 kRC90107			= 90107; //��ϵ�������SNS������
	const INT32 kRC90108			= 90108; //����ڵ�Ͻ���
	const INT32 kRC90109			= 90109; //����������ʵ�Ͻ���
	const INT32 kRC90110			= 90110; //����ڵ�޵�Ͻ���
	const INT32 kRC90111			= 90111; //SNS������Ͻ���
	const INT32 kRC90112			= 90112; //�����ʺ���Ұ�(���ڵ���ų������������)
	const INT32 kRC90113			= 90113; //�̵̹�ϵ�SNS��������������
	const INT32 kRC90114			= 90114; //�������SNS������
	const INT32 kRC90115			= 90115; //SNS��������ġ��������
	const INT32 kRC90116			= 90116; //Email�������
	const INT32 kRC90117			= 90117; //Nickname��������
	const INT32 kRC90118			= 90118; //SNS�������º������
	const INT32 kRC90119			= 90119; //Nickname���º������
	const INT32 kRC90120			= 90120; //Nickname�ߺ�����
	const INT32 kRC90121			= 90121; //Nickname�����
	const INT32 kRC90122			= 90122; //Nickname�����׺���Ϸ�ó������
	const INT32 kRC90123			= 90123; //�̹�����ó����email��
	const INT32 kRC90124			= 90124; //������ǻ��´��ش��۾�����Ұ���
	const INT32 kRC90125			= 90125; //�����׷�������ξ��ߺ�����
	const INT32 kRC90126			= 90126; //UserID���̿���
	const INT32 kRC90127			= 90127; //Password���̿���
	const INT32 kRC90128			= 90128; //Email���̿���
	const INT32 kRC90129			= 90129; //�������Ϲ߼ۿ���
	const INT32 kRC90130			= 90130; //SNS������������
	const INT32 kRC90131			= 90131; //�����н�����
	const INT32 kRC90132			= 90132; //���� ���� path��� ����

	const INT32 kRC90201			= 90201; //����Ű���೻���̾���
	const INT32 kRC90202			= 90202; //����Ű���Ѹ���
	const INT32 kRC90203			= 90203; //��������Ű��
	const INT32 kRC90204			= 90204; //Key���º������
	const INT32 kRC90205			= 90205; //Key������
	const INT32 kRC90206			= 90206; //�����̿��������ʿ�
	const INT32 kRC90207			= 90207; //SC��뼱���ߺ�����
	const INT32 kRC90208			= 90208; //�����̿����ߺ�����
	const INT32 kRC90209			= 90209; //��밡�ɿ��������
	const INT32 kRC90210			= 90210; //������ߺ���Ͽ���
	const INT32 kRC90211			= 90211; //�α��ν���ȸ���ʰ�
	const INT32 kRC90212			= 90212; //����Ű�߱޽���
	const INT32 kRC90213			= 90213; //��ȿ������������Ű
	const INT32 kRC90214			= 90214; //����Ű��������ġ
	const INT32 kRC90215			= 90215; //������ο��������
	const INT32 kRC90216			= 90216; //�̹̺�Ȱ��ȭ(����)ó���Ǿ���
	const INT32 kRC90217			= 90217; //���ӺҰ������ǻ������
	const INT32 kRC90222			= 90222; //���ǵ��� ���� ����(���� DB)

	const INT32 kRC90301			= 90301; //��å��ȣ����
	const INT32 kRC90302			= 90302; //��å���ع�ȣ����
	const INT32 kRC90303			= 90303; //���ǵ���å����
	const INT32 kRC90304			= 90304; //�̹����ǵ���å��
	const INT32 kRC90305			= 90305; //�������ӺҰ�����
	const INT32 kRC90306			= 90306; //�������ӺҰ�����
	const INT32 kRC90307			= 90307; //��û�ѻ�����Ǳ��������������Ҽ�����PG
	const INT32 kRC90308			= 90308; //��û�ѻ�����Ǻ���������δ������Ҽ�����PG
	const INT32 kRC90309			= 90309; //����ں�����޺��������ѵ��ʰ�
	const INT32 kRC90310			= 90310; //����ں�����޺��������ѵ��ʰ�
	const INT32 kRC90311			= 90311; //���������������
	const INT32 kRC90312			= 90312; //������å����Ǿ�������
	const INT32 kRC90313			= 90313; //�������̽����������Դϴ�.
	const INT32 kRC90314			= 90314; //��å����ó������
	const INT32 kRC90315			= 90315; //������������Ѹ���ó������
	const INT32 kRC90316			= 90316; //���� �Ұ� ä�θ�
	const INT32 kRC90317			= 90317; //��û�� ä�θ������� ������ �� ���� PG
	const INT32 kRC90318			= 90318; //���� �Ұ� PII
	const INT32 kRC90319			= 90319; //������������ ���� ���� ���� �Ұ�
	const INT32 kRC90320			= 90320; //���� ������ ������(�ش� ���ӿ� ����)
	const INT32 kRC90321			= 90321; //�������� ���� IP
	const INT32 kRC90322			= 90322; //��ϵ��� ���� ���� �ڵ�

	const INT32 kRC90401			= 90401; //���񽺺��������׷��ߺ�����
	const INT32 kRC90402			= 90402; //���񽺺��������׷�з��ߺ�����
	const INT32 kRC90403			= 90403; //�ش��������׷����
	const INT32 kRC90404			= 90404; //�̵��Խù��̾���
	const INT32 kRC90405			= 90405; //�̵�����ش��̹��������������ߺ�����
	const INT32 kRC90406			= 90406; //�ش��������׷�з�����
	const INT32 kRC90407			= 90407; //�Խñۼ�/��ۼ�/��ȸ����������
	const INT32 kRC90408			= 90408; //��۵�ϺҰ���������
	const INT32 kRC90409			= 90409; //��۵�Ͻ���
	const INT32 kRC90410			= 90410; //���ӽ��������ߺ�����
	const INT32 kRC90411			= 90411; //CDN��Ʈ�������Է��ʿ�
	const INT32 kRC90412			= 90412; //�ٿ�ε弭�����������Է��ʿ�
	const INT32 kRC90413			= 90413; //��������Է��ʿ�
	const INT32 kRC90414			= 90414; //�ٿ�ε�����������������
	const INT32 kRC90415			= 90415; //�ٱ��� ���� ��� ����
	const INT32 kRC90416			= 90416; //��� ���� �ʰ�

	const INT32 kRC90501			= 90501; //EM��Ͽ���
	const INT32 kRC90502			= 90502; //EM���º������
	const INT32 kRC90503			= 90503; //EM����ߺ���Ͽ���
	const INT32 kRC90504			= 90504; //EM����Ͽ���
	const INT32 kRC90505			= 90505; //EM�����º������
	const INT32 kRC90506			= 90506; //EM���۽����ߺ�����

	const INT32 kRC90601			= 90601; //FAQ��Ͽ���
	const INT32 kRC90602			= 90602; //FAQ�����������(���º�������)
	const INT32 kRC90603			= 90603; //FAQ��ȸ��,LIKE������ó������
	const INT32 kRC90604			= 90604; //�������1:1���ǵ�Ͽ���
	const INT32 kRC90605			= 90605; //�������1:1���Ǵ��������(����)����
	const INT32 kRC90606			= 90606; //�������1:1���ǻ��º������
	const INT32 kRC90607			= 90607; //�������1:1���Ǵ亯��Ͽ���
	const INT32 kRC90608			= 90608; //�������1:1���Ǵ亯�������(���º�������)
	const INT32 kRC90609			= 90609; //�������1:1����÷�������ߺ�����
	const INT32 kRC90610			= 90610; //Ƽ���� �ƴ� (check)
	const INT32 kRC90611			= 90611; //Ƽ�� ���� Fault Exception (check)
	const INT32 kRC90612			= 90612; //Ƽ�� ���� Exception (check)
	const INT32 kRC90613			= 90613; //Ƽ���� �ƴ� (use)
	const INT32 kRC90614			= 90614; //Ƽ�� ���� Fault Exception (use)
	const INT32 kRC90615			= 90615; //Ƽ�� ���� Exception (use)
	const INT32 kRC90616			= 90616; //��� �����ڰ� �ƴ�
	const INT32 kRC90617			= 90617; //ó���Ұ� ���ǻ�����
	const INT32 kRC90618			= 90618; //�ش� ������� ���ǻ����� �ƴ�
	const INT32 kRC90619			= 90619; //�ٱ��� ���� ��� ����
	const INT32 kRC90620			= 90620; //���� ��� �Ұ� ���(�����/cs�����)��
	const INT32 kRC90621			= 90621; //ī�װ��� ���� ī�װ� ���� ����

	const INT32 kRC90701			= 90701; //��������ڵ�Ͽ���
	const INT32 kRC90702			= 90702; //��������������������
	const INT32 kRC90703			= 90703; //���������ߺ���Ͽ���
	const INT32 kRC90704			= 90704; //�������ܵ�Ͽ���
	const INT32 kRC90705			= 90705; //�������������������
	const INT32 kRC90706			= 90706; //������ǰ�ߺ���Ͽ���
	const INT32 kRC90707			= 90707; //������ǰ��Ͽ���
	const INT32 kRC90708			= 90708; //������ǰ�����������
	const INT32 kRC90709			= 90709; //�Ǹž������ߺ���Ͽ���
	const INT32 kRC90710			= 90710; //�Ǹž����۵�Ͽ���
	const INT32 kRC90711			= 90711; //�Ǹž����������������
	const INT32 kRC90712			= 90712; //������û�ߺ���Ͽ���
	const INT32 kRC90713			= 90713; //������û��Ͽ���
	const INT32 kRC90714			= 90714; //����Ȯ��ó������
	const INT32 kRC90715			= 90715; //�����Ϸ�ó������
	const INT32 kRC90716			= 90716; //��������ó������
	const INT32 kRC90717			= 90717; //����Ʈ������ߺ���Ͽ���
	const INT32 kRC90718			= 90718; //����Ʈ����ǵ�Ͽ���
	const INT32 kRC90719			= 90719; //�ܾ��ߺ���Ͽ���
	const INT32 kRC90720			= 90720; //�ܾ׵�Ͽ���
	const INT32 kRC90721			= 90721; //�ܾ�����ó������
	const INT32 kRC90722			= 90722; //PGhandshaking����
	const INT32 kRC90726			= 90726; //��ٱ����ߺ���Ͽ���
	const INT32 kRC90727			= 90727; //��ٱ��ϵ�Ͽ���
	const INT32 kRC90728			= 90728; //PGStartToken��ȸ����
	const INT32 kRC90729			= 90729; //���Ż��º������
	const INT32 kRC90730			= 90730; //����ó������
	const INT32 kRC90731			= 90731; //����ó�����ܾ׺�������
	const INT32 kRC90732			= 90732; //���ŵ�Ͽ���
	const INT32 kRC90733			= 90733; //�������ó������
	const INT32 kRC90734			= 90734; //ȯ���̾ȵǴ°�������
	const INT32 kRC90735			= 90735; //ȯ���ߺ���Ͽ���
	const INT32 kRC90736			= 90736; //ȯ�ҵ�Ͽ���
	const INT32 kRC90737			= 90737; //ȯ��ó������
	const INT32 kRC90738			= 90738; //���� ������ �ƴ� (check)
	const INT32 kRC90739			= 90739; //���� ���� Fault Exception (check)
	const INT32 kRC90740			= 90740; //���� ���� Exception (check)
	const INT32 kRC90741			= 90741; //���� ������ �ƴ� (use)
	const INT32 kRC90742			= 90742; //���� ���� Fault Exception (use)
	const INT32 kRC90743			= 90743; //���� ���� Exception (use)
	const INT32 kRC90744			= 90744; //���� ���� Ȯ�� ���� ������ ���� ��ǰ���� ����
	const INT32 kRC90745			= 90745; //���� ���� Ȯ�� ��õ� ��� ���� ������ ���� ��ǰ���� ����
	const INT32 kRC90746			= 90746; //���� ���� Ȯ�� ��õ� ����� ����
	const INT32 kRC90747			= 90747; //���� ���� Ȯ�� ��õ� Exception
	const INT32 kRC90748			= 90748; //���� ���� Ȯ�� ����
	const INT32 kRC90749			= 90749; //���� ���� Ȯ�� Exception
	const INT32 kRC90750			= 90750; //���� ���� Ȯ�� ����
	const INT32 kRC90751			= 90751; //ȯ�� �ȵǴ� ������ (�������� ������)
	const INT32 kRC90752			= 90752; //SKT ���� Ȯ�� ����
	const INT32 kRC90753			= 90753; //SKT ���� Ȯ�� ���� (�� ����)
	const INT32 kRC90754			= 90754; //SKT ���� Ȯ�� ���� ������ ���� ��ǰ���� ����
	const INT32 kRC90755			= 90755; //SKT ���� Ȯ�� Exception
	const INT32 kRC90756			= 90756; //���� Ƚ�� �ʰ�
	const INT32 kRC90757			= 90757; //�Ǹ� ���� �ʰ�
	const INT32 kRC90758			= 90758; //ù ���� ���� �Ұ�
	const INT32 kRC90759			= 90759; //���� ���� ������ ����
	const INT32 kRC90760			= 90760; //���� ����Ȯ�� Exception
	const INT32 kRC90761			= 90761; //ĳ�û������

	const INT32 kRC90801			= 90801; //��ȿ�����������θ��
	const INT32 kRC90802			= 90802; //��ȿ�����������θ����Ʈ��
	const INT32 kRC90803			= 90803; //��ȿ����������������
	const INT32 kRC90804			= 90804; //��ȿ�������������׷�
	const INT32 kRC90805			= 90805; //��ȿ��������������ǰ
	const INT32 kRC90806			= 90806; //�����׷��ǰ�߰��Ұ�
	const INT32 kRC90807			= 90807; //�Ӽ���������
	const INT32 kRC90808			= 90808; //�Ӽ��÷��׼�������
	const INT32 kRC90809			= 90809; //����ż�����
	const INT32 kRC90810			= 90810; //��������������������
	const INT32 kRC90811			= 90811; //��ȿ��������serial
	const INT32 kRC90812			= 90812; //�������Ұ������
	const INT32 kRC90813			= 90813; //��밡�ɰ����ʰ�
	const INT32 kRC90814			= 90814; //���ó����Ͽ���
	const INT32 kRC90815			= 90815; //���������Ͽ���
	const INT32 kRC90816			= 90816; //�̹̻���������
	const INT32 kRC90817			= 90817; //����ʱ�ȭ��������
	const INT32 kRC90818			= 90818; //�����׷��ǰ����
	const INT32 kRC90819			= 90819; //���θ�ǻ��º������
	const INT32 kRC90820			= 90820; //���θ����Ʈ�ʻ��º������
	const INT32 kRC90821			= 90821; //�����׷���º������
	const INT32 kRC90822			= 90822; //�����׷��ǰ���º������
	const INT32 kRC90823			= 90823; //���θ����Ʈ��contracttype�������
	const INT32 kRC90824			= 90824; //period�������
	const INT32 kRC90825			= 90825; //��ȿ�������������׷�����
	const INT32 kRC90826			= 90826; //��ȿ�������������׷��ǰ
	const INT32 kRC90827			= 90827; //��ȿ���������Ӽ�
	const INT32 kRC90828			= 90828; //��û Ʈ����� �ߺ� ��� ����
	const INT32 kRC90829			= 90829; //��ȿ���� ���� ��� ����
	const INT32 kRC90830			= 90830; //���� ���� ���� �ż� ����
	const INT32 kRC90831			= 90831; //���� ���� ���� ����
	const INT32 kRC90832			= 90832; //�Ӽ� ���� �Ұ� (���� ������ �ִ� ���)

	const INT32 kRC90901			= 90901; //���������Է¿���
	const INT32 kRC90902			= 90902; //��ȿ��������������
	const INT32 kRC90903			= 90903; //�Ⱓ�����Է¿���
	const INT32 kRC90904			= 90904; //�ǸżӼ������Է¿���
	const INT32 kRC90905			= 90905; //���������������
	const INT32 kRC90906			= 90906; //�ߺ��Ⱦ������Ǹ�������
	const INT32 kRC90907			= 90907; //���ø���Ʈ���̹�������
	const INT32 kRC90908			= 90908; //��ȿ�����������ſ�û������
	const INT32 kRC90909			= 90909; //��ȿ�������������κ��丮����
	const INT32 kRC90910			= 90910; //�����ۼ��ɿ���
	const INT32 kRC90911			= 90911; //�����۰��ݿ���
	const INT32 kRC90912			= 90912; //�����۱��Ű��ɷ����̳���������ġ
	const INT32 kRC90913			= 90913; //�����۱����ѵ��ʰ�
	const INT32 kRC90914			= 90914; //�ش�����۱��źҰ��������
	const INT32 kRC90915			= 90915; //�Ǹ��ܿ���������
	const INT32 kRC90916			= 90916; //1ȸ���Ű��ɼ�������
	const INT32 kRC90917			= 90917; //�籸�����ѿ���
	const INT32 kRC90918			= 90918; //�����κ��丮��Ͻ���
	const INT32 kRC90919			= 90919; //�����������κ��丮��Ͻ���
	const INT32 kRC90920			= 90920; //���Ǿ������κ��丮��Ͻ���
	const INT32 kRC90921			= 90921; //���ʽ��������κ��丮��Ͻ���
	const INT32 kRC90922			= 90922; //�����κ��丮��������
	const INT32 kRC90923			= 90923; //���ɰ��ɾ������̾���
	const INT32 kRC90924			= 90924; //��ȿ��������ī�װ�
	const INT32 kRC90925			= 90925; //��ȿ������������
	const INT32 kRC90926			= 90926; //īƮ������������
	const INT32 kRC90927			= 90927; //��ϴ��������̾���
	const INT32 kRC90928			= 90928; //�θ�(��Ű��/����/���ʽ�)��������������
	const INT32 kRC90929			= 90929; //�����������������
	const INT32 kRC90930			= 90930; //����ĳ��������������
	const INT32 kRC90931			= 90931; //�θ���������Ǹ�������������
	const INT32 kRC90932			= 90932; //���ɼ�������
	const INT32 kRC90933			= 90933; //�ҷɷαױ�Ͻ���
	const INT32 kRC90934			= 90934; //�����κ��丮���ɽ���
	const INT32 kRC90935			= 90935; //�����������κ��丮���ɽ���
	const INT32 kRC90936			= 90936; //���Ǿ������κ��丮���ɽ���
	const INT32 kRC90937			= 90937; //���ʽ��������κ��丮���ɽ���
	const INT32 kRC90938			= 90938; //����������ߺ���Ͽ���
	const INT32 kRC90939			= 90939; //���Ǻ�����������
	const INT32 kRC90940			= 90940; //���αⰣ�ߺ�����
	const INT32 kRC90941			= 90941; //��ȿ�����������Ӽ�������
	const INT32 kRC90942			= 90942; //��ȿ��������ī������
	const INT32 kRC90943			= 90943; //�����Ұ���������
	const INT32 kRC90944			= 90944; //���� �Ұ� �׸� ���� ����
	const INT32 kRC90945			= 90945; //�Ǹ� ĳ�� ���� ���� ����
	const INT32 kRC90946			= 90946; //������ ���ʽ� ���� ���� ���� ����
	const INT32 kRC90947			= 90947; //������ ������ �ƴ� (check)
	const INT32 kRC90948			= 90948; //������ ���� ��ȸ ���� (check)
	const INT32 kRC90949			= 90949; //������ ���� ã�� �� ���� (check)
	const INT32 kRC90950			= 90950; //���� ���� Fault Exception (check)
	const INT32 kRC90951			= 90951; //���� ���� Exception (check)
	const INT32 kRC90952			= 90952; //������ ������ �ƴ� (use)
	const INT32 kRC90953			= 90953; //���� ���� Fault Exception (use)
	const INT32 kRC90954			= 90954; //���� ���� Exception (use)
	const INT32 kRC90955			= 90955; //�θ� ī�װ� ���� ����
	const INT32 kRC90956			= 90956; //�������� ���� �� ���� ī�װ���
	const INT32 kRC90957			= 90957; //���� �Ұ� ������ �Ǹ� ������
	const INT32 kRC90958			= 90958; //����/�ϰ� ���� �Ұ�����
	const INT32 kRC90959			= 90959; //������ ���� ��� �Ұ�
	const INT32 kRC90960			= 90960; //īƮ/���ø���Ʈ ���� �ִ� ���� �ʰ�
	const INT32 kRC90961			= 90961; //īƮ/���ø���Ʈ ��� �Ұ� ������
	const INT32 kRC90962			= 90962; //��ȿ���� ���� ������ ����
	const INT32 kRC90963			= 90963; //WCoin ���� ������ ���� ���� ����
	const INT32 kRC90964			= 90964; //��Ű�� ������, ���� ���� �Ұ�
	const INT32 kRC90965			= 90965; //��Ű��/���� ������, �ٸ� ��Ű�� Ȥ�� ���ʽ� ���� ������ ���� �Ұ�
	const INT32 kRC90966			= 90966; //�ϰ� ���� ���� ���� ���� ����
	const INT32 kRC90967			= 90967; //�ϰ� ���� ���� ���� ���� ����
	const INT32 kRC90968			= 90968; //���� �ݾ� ����ġ
	const INT32 kRC90969			= 90969; //�ֹ���ȣ �ߺ�
	const INT32 kRC90970			= 90970; //���� öȸ�� ��� ������ ����
	const INT32 kRC90971			= 90971; //ä�θ�Ű�� ���� ����� ���� ��� ����
	const INT32 kRC90972			= 90972; //���� ���� ȸ�� ����

	const INT32 kRC91101			= 91101; //��ȿ���� ���� GameCode ��
	const INT32 kRC91102			= 91102; //IP Ȯ�� ����

	const INT32 kRC91201			= 91201; //������ ��� ����
	const INT32 kRC91202			= 91202; //2.0 ������ ����ȭ ����

	const INT32 kRC91301			= 91301; //��ȿ���� ���� ä�θ� ��Ʈ�ʻ���
	const INT32 kRC91302			= 91302; //ä�θ� ����� �⺻ ���� ��� ����
	const INT32 kRC91303			= 91303; //ä�θ� ����� ���� ��� ����
	const INT32 kRC91304			= 91304; //ä�θ� ����� ���� �� ��� ����
	const INT32 kRC91305			= 91305; //��ȿ���� ���� ä�θ� ���� ����
	const INT32 kRC91306			= 91306; //��ȿ���� ���� ä�θ� ��Ʈ�� ���� ����
	const INT32 kRC91307			= 91307; //�̹� ä�θ� ��ϵ� ������
	const INT32 kRC91308			= 91308; //ä�θ� ���� ����
	const INT32 kRC91309			= 91309; //ä�θ� ���� ����
	const INT32 kRC91310			= 91310; //�ٸ� ä�θ� ��Ʈ�ʻ翡 ��ϵ� ������

	const INT32 kRC91401			= 91401; //�̹� �߼� �Ǿ���

	const INT32 kRC91501			= 91501; //�ۺ��� API ���� ����
	const INT32 kRC91502			= 91502; //�ۺ��� ���� ����


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 3 Condition Types
	const BYTE kCT_None       					 	= 0x00; //�⺻��         
	const BYTE kCT_ConflictConfigurationVersion		= 0x14; //�������� �����
	const BYTE kCT_ConflictProductVersion			= 0x15; //��ǰ���� �����
	const BYTE kCT_Running                          = 0x64; //���� ���� ���� 
	const BYTE kCT_Stop                             = 0x65; //���� ����      
	const BYTE kCT_Maintenance                      = 0xFF; //���� ��        


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 4 Return Structure Types
	const BYTE kRST_Default	    = 0x00; //�⺻                           
	const BYTE kRST_XML         = 0x01; //XML Type                       
	const BYTE kRST_JSON        = 0x02; //JSON Type(http://www.json.org/)
	const BYTE kRST_Exclusion   = 0xFF; //Return Structure ����                                 


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 5 Sales Types
	const BYTE kST_None					= 0x00; //���ǵ��� ����                 
	const BYTE kST_CCoin				= 0x01; //C Coin (System Code: TRT001)
	const BYTE kST_PCoin				= 0x02; //P Coin (System Code: TRT002)
	const BYTE kST_ComplexCoin			= 0x03; //C+P Coin (System Code: TRT011)
	const BYTE kST_FlatRate				= 0x04; //P Coin ���� (System Code: TRT022)
	const BYTE kST_ETC					= 0x05; //��Ÿ (System Code: TRT005)
	const BYTE kST_CCoinFlatRate		= 0x06; //C Coin����(System Code: TRT002)
	const BYTE kST_ComplexCoinFlatRate	= 0x07; //C+P Coin ����(System Code: TRT012)
                                                                            

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 6 Authorization Use Status Type
	const wchar_t kSTS210[7] = L"STS210";	//Activation ��                                   
	const wchar_t kSTS211[7] = L"STS211";	//Activation ��                                   
	const wchar_t kSTS212[7] = L"STS212";	//��� ��                                         
	const wchar_t kSTS213[7] = L"STS213";	//�������(�����ڿ� ����)                         
	const wchar_t kSTS214[7] = L"STS214";	//�������(���� ȯ�ҿ� ���� ���)                 
	const wchar_t kSTS215[7] = L"STS215";	//�������(���� ȯ�ҿ� ���� �κ����)             
	const wchar_t kSTS216[7] = L"STS216";	//��븸��(���Ⱓ ���)                         
	const wchar_t kSTS217[7] = L"STS217";	//��븸��(��� ���� �� ���� ȯ�ҿ� ���� ���)    
	const wchar_t kSTS218[7] = L"STS218";	//��븸��(��� ���� �� ���� ȯ�ҿ� ���� �κ����)
	const wchar_t kSTS219[7] = L"STS219";	//��븸��(Ȱ��ȭ ��ȿ�Ⱓ ���)                  


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 7 Authorization User Type (1.2.2 ���忡�� �����)
	const wchar_t kSUT001[7] = L"SUT001";	//�Ϲ� �����
	const wchar_t kSUT002[7] = L"SUT002";	//GM
	const wchar_t kSUT003[7] = L"SUT003";	//Tester

	//const wchar_t kUST001[7] = L"UST001";	//�Ϲ� �����
	//const wchar_t kUST002[7] = L"UST002";	//�� ������  
	//const wchar_t kUST003[7] = L"UST003";	//GM         
	//const wchar_t kUST004[7] = L"UST004";	//QA         
	//const wchar_t kUST005[7] = L"UST005";	//Partner    
	//const wchar_t kUST006[7] = L"UST006";	//Tester     
                                                                         
	/////////////////////////////////////////////////////////////////////////////////////
	// Table 8 Authorization User Status
	const wchar_t kSTS120[7] = L"STS120";	//���Խ�û(���)
	const wchar_t kSTS121[7] = L"STS121";	//�����Ϸ�(����)
	const wchar_t kSTS122[7] = L"STS122";	//���� ��       
	const wchar_t kSTS123[7] = L"STS123";	//Ż��          
	const wchar_t kSTS124[7] = L"STS124";	//����Ż��      
	const wchar_t kSTS125[7] = L"STS125";	//���� ��       

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 9 Authorization Security Provider Type
	const wchar_t kSCT001[7] = L"SCT001";		//�Ϲݻ����
	const wchar_t kSCT002[7] = L"SCT002";		//SCī�� ���

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 10 Data Types
	//	N/A

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 11 Inquiry Cash Inventory Expand Flags
	const BYTE kICIEF_Purchase	= 0x00; //�ֹ� ������
	const BYTE kICIEF_Package	= 0x01; //��Ű�� ������
	const BYTE kICIEF_Lottery	= 0x02; //���� ������
	const BYTE kICIEF_Bonus		= 0x04; //���ʽ� ������
	const BYTE kICIEF_All		= 0x07; //��ü (Order | Package | Lottery | Bonus)

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 12 Inquiry Item Status Flags
	const INT32 kIISF_Disabled	= -1;	//�Ǹ����� ������
	const INT32 kIISF_Enabled	= 0x00; //�Ǹ� ������
	const INT32 kIISF_New		= 0x01; //�ű� ������
	const INT32 kIISF_Event		= 0x02; //�̺�Ʈ ������
	const INT32 kIISF_Limited	= 0x04; //���� ������
	const INT32 kIISF_Hot		= 0x08; //�α� ������
	const INT32 kIISF_Best		= 0x10; //����Ʈ ������
	const INT32 kIISF_Reserved	= 0x20; //���� ������
	const INT32 kIISF_Sales		= 0x40; //���� ������
	const INT32 kIISF_All		= 0x7F; //��ü (Enabled | New | Event | Limited | Hot | Best | Reserved | Sales)

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 13 Inquiry Item Order by Type
	const BYTE kIIOBT_Default				= 0; //���� �⺻ ��
	const BYTE kIIOBT_ItemNameAscending		= 1; //������ �̸� ��
	const BYTE kIIOBT_ItemNameDescending	= 2; //������ �̸� ����
	const BYTE kIIOBT_ItemAmountAscending	= 3; //���� ����
	const BYTE kIIOBT_ItemAmountDescending	= 4; //�ְ� ����


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 14 Inquiry Expand Flags
	const INT32 kIEF_MainItems				= 0x00; //�⺻ ������
	const INT32 kIEF_PackageItems			= 0x01; //��Ű�� ������
	const INT32 kIEF_LotteryItems			= 0x02; //���� ������
	const INT32 kIEF_LinkageItems			= 0x04; //���� ������
	const INT32 kIEF_RecommendationItems	= 0x08; //��õ ������
	const INT32 kIEF_BonusItems				= 0x10; //���ʽ� ������
	const INT32 kIEF_ItemProperties			= 0x20; //������ �Ӽ�


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 15 Inquiry Cart & Wish Expand Flags
	const INT32 kICWEF_Default			= 0x00; //����īƮ �Ǵ� ���þ�����
	const INT32 kICWEF_ItemProperties	= 0x01; //������ �Ӽ�
	const INT32 kICWEF_LinkageItems		= 0x02; //���� ������
	const INT32 kICWEF_All				= 0x03; //��ü (Default | Properties | Linkage)
	
	/////////////////////////////////////////////////////////////////////////////////////
	// Table 16 Execute Method Type
	const BYTE kEMT_Discounts			= 0x00; //����������ȸ
	const BYTE kEMT_GameWorlds			= 0x01; //���ӿ��忡���ѱ⺻����
	const BYTE kEMT_Categories			= 0x02; //ī�װ��⺻����
	const BYTE kEMT_Properties			= 0x03; //�Ӽ��⺻����
	const BYTE kEMT_Tags				= 0x04; //�±ױ⺻����
	const BYTE kEMT_CategoryWorlds		= 0x05; //���ӿ��忡�����ī�װ�����
	const BYTE kEMT_ProductCategories	= 0x06; //ī�װ�������Ⱦ���������
	const BYTE kEMT_ProductProperties	= 0x07; //��ǰ������ȼӼ�����
	const BYTE kEMT_ProductTags			= 0x08; //��ǰ��������±�����
	const BYTE kEMT_Products			= 0x09; //��ǰ�⺻����
	const BYTE kEMT_ProductSales		= 0x0A; //��ǰ�Ǹ�����
	const BYTE kEMT_ProductPackages		= 0x0B; //��ǰ���������Ű������
	const BYTE kEMT_ProductLotteries	= 0x0C; //��ǰ������Ⱥ�������
	const BYTE kEMT_ProductBonuses		= 0x0D; //��ǰ������Ⱥ��ʽ�����
	const BYTE kEMT_ProductLinkage		= 0x0E; //��ǰ������ȿ�����ǰ����
	const BYTE kEMT_ProductRecommends	= 0x0F; //��ǰ���������õ��ǰ

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 18 Cash Type
	enum saleCoinType {
		kSCT_UNKNOWN = 0,
		kSCT_WCOIN = 1,												 // ���� ����
		kSCT_REDGEN,												 // ������
		kSCT_IMPUTATION_REDGEN										 // �ͼӷ�����
	};
	
	/////////////////////////////////////////////////////////////////////////////////////
	// ETC. Receive Type : �޴� Ÿ��
	const BYTE kRTRequest			= 0x01; //��û����
	const BYTE kRTAuto				= 0x02; //�ڵ�����
	const BYTE kRTForce				= 0x03; //��������
	const BYTE kRTExpiredForce		= 0x04; //���ᰭ������
	const BYTE kRTDelete			= 0x05; //����
	const BYTE kRTExpiredDelete		= 0x06; //�������

	/////////////////////////////////////////////////////////////////////////////////////
	// ETC. Inventory Type : �κ��丮 Ÿ��
	const BYTE kITPackageInventories	= 0x01; //Package Inventories
	const BYTE kITLotteryInventories	= 0x02; //Lottery Inventories
	const BYTE kITBonusInventories		= 0x04; //Bonus Inventories

	/////////////////////////////////////////////////////////////////////////////////////
	// ETC. Inventory Status : �κ��丮 ����
	const BYTE kISImmediately	= 0x1F; //��ü���
	const BYTE kISPickup		= 0x05; //�Ⱦ��� ���� ����

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 25 Order Status
	enum orderStatus {
		kOS_NOT_ORDERED = 0,	// �ֹ� ��û �ȵ� (�ֹ�����/��� �Ұ�)
		kOS_ORDERED = 1,		// �ֹ� ��û�� (�ֹ�����/��� ����)
		kOS_CONFIRMED,			// �ֹ� ���ε� (�ֹ���� �Ұ�)
		kOS_CANCELED			// �ֹ� ��ҵ� (�ֹ����� �Ұ�)
	};


} // namespace

#endif
