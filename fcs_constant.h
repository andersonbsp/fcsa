#ifndef FCSADAPTER_INTERFACE_CONSTANT_H_
#define FCSADAPTER_INTERFACE_CONSTANT_H_

namespace fcsa {

	/////////////////////////////////////////////////////////////////////////////////////
	// Reserved Character : 모든 패킷의 첫번째 BYTE의 예약 문자
	const BYTE kReservedCharacter								 = 0xFF;

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 1 Packet Types
	// Common
	const BYTE kPacketType_Initialize									= 0x01; //Front Channel Service에 연결     
	const BYTE kPacketType_KeepAlive									= 0x02; //연결상태 확인                    
	// Authentication & Authorization
	const BYTE kPacketType_GameLogin									= 0x11; //게임로그인                       
	const BYTE kPacketType_GameLogout									= 0x12; //게임로그아웃                     
	const BYTE kPacketType_PremiumServiceExpiredCallback				= 0x13; //프리미엄 서비스 기간 만료 통보   
	const BYTE kPacketType_ForceUserLogoutCallback						= 0x14; //사용자 강제 로그아웃             
	const BYTE kPacketType_RequestAuthenticationKey						= 0x21; //인증키 요청                      
	const BYTE kPacketType_ValidateAuthenticationKey					= 0x22; //인증키 유효성 확인               
	const BYTE kPacketType_ValidateAuthenticationKeyWithExtension		= 0x23; //인증키 유효성 확인               
	const BYTE kPacketType_ValidateAuthenticationKeyForPublisher		= 0x24; //인증키 유효성 확인
	const BYTE kPacketType_ValidateAuthenticationKeyWithParentSafe		= 0x25;	//부모 안심 서비스 인증키 유효성 검사
	const BYTE kPacketType_ValidateAuthenticationKeyForR2				= 0x26; //국내 R2 용 인증키 유효성 검사
	const BYTE kPacketType_ValidateAuthenticationKeyWithUserInfo		= 0x27; //인증키 유효성 확인(유저 정보 조회)
	const BYTE kPacketType_AccountLogin									= 0x31; //WEBZEN Account Login
	const BYTE kPacketType_AccountLogout								= 0x32; //WEBZEN Account Logout
	const BYTE kPacketType_SetAccountState								= 0x33; //계정의 마지막 로그인/로그아웃 정보 업데이트
	const BYTE kPacketType_GetPCRoomGuid								= 0x34; //IP로 PC방 고유번호 반환
	const BYTE kPacketType_CheckPhoneAuthUser							= 0x35; //전화인증 가입계정 여부 확인
	const BYTE kPacketType_GetUserInfo									= 0x36; //계정번호로 사용자 정보 확인
	const BYTE kPacketType_GetUserInfoWithExtension						= 0x37; //계정번호로 사용자 정보 확인
	const BYTE kPacketType_ActivateFlatRatePaymentProduct				= 0x41; //정액상품 활성화                  
	const BYTE kPacketType_DeactivateFlatRatePaymentProduct				= 0x42; //정액상품 비활성화                
	// Basic Billing
	const BYTE kPacketType_CheckBalance									= 0x51; //잔액조회                         
	const BYTE kPacketType_ItemPurchase									= 0x61; //복수 아이템 구매                 
	const BYTE kPacketType_ItemGift										= 0x62; //복수 아이템 선물                 
	const BYTE kPacketType_CheckPurchase								= 0x63; //구매확인                         
	const BYTE kPacketType_CancelPurchase								= 0x64; //구매취소                         
	const BYTE kPacketType_CancelPurchaseByOrderId						= 0x65; //주문번호를 이용해서 전체 구매취소
	const BYTE kPacketType_ConfirmPurchaseByOrderId						= 0x66; //주문번호를 이용해서 전체 구매승인
	const BYTE kPacketType_PurchaseList									= 0x71; //구매내역조회
	const BYTE kPacketType_ExchangeWCoin								= 0x72; //WCoin을 게임 내에서 사용되는 포인트로 전환
	// WShop Billing
	const BYTE kPacketType_WShopCheckBalance                            = 0x90; //잔액조회
	const BYTE kPacketType_WShopPurchase                                = 0x91; //샵 아이템 구매
	const BYTE kPacketType_WShopCheckPurchase                           = 0x92; //샵 아이템 구매 확인
	const BYTE kPacketType_WShopCancelPurchase                          = 0x93; //샵 아이템 구매 취소
	const BYTE kPacketType_WShopConfirmPurchase                         = 0x94; //샵 아이템 구매 승인
	const BYTE kPacketType_WShopGift                                    = 0x95; //샵 아이템 선물
	const BYTE kPacketType_WShopCheckGift                               = 0x96; //선물 건 확인
	const BYTE kPacketType_WShopCancelGift                              = 0x97; //선물 건 취소
	const BYTE kPacketType_WShopConfirmGift                             = 0x98; //쥬얼 충전 건 승인
	const BYTE kPacketType_WShopGetVersion                              = 0x99; //샵 버전 정보 조회
	// WShop Inventory
	const BYTE kPacketType_WShopInquiryNewArrival                       = 0x9A; //일자 기준으로 새로 들어온 인벤토리 아이템 조회
	const BYTE kPacketType_WShopInquiryInventory                        = 0x9B; //인벤토리 조회	
	const BYTE kPacketType_WShopPickUp                                  = 0x9C; //인벤토리 수령
	const BYTE kPacketType_WShopCheckPickUp                             = 0x9D; //인벤토리 수령 건 확인
	const BYTE kPacketType_WShopCancelPickUp                            = 0x9E; //인벤토리수령건취소
	const BYTE kPacketType_WShopConfirmPickUp                           = 0x9F; //인벤토리수령건승인
	//Jewel
	const BYTE kPacketType_ChargeJewel                                  = 0xB0; //쥬얼충전요청
	const BYTE kPacketType_CheckJewelCharge                             = 0xB1; //쥬얼충전건확인
	const BYTE kPacketType_CancelJewelCharge                            = 0xB2; //쥬얼충전건취소
	const BYTE kPacketType_ConfirmJewelCharge                           = 0xB3; //쥬얼충전건승인
	const BYTE kPacketType_PurchaseJewelItem                            = 0xB4; //쥬얼소진
	const BYTE kPacketType_CheckPurchaseJewel                           = 0xB5; //쥬얼소진건확인
	const BYTE kPacketType_CancelJewelPurchase                          = 0xB6; //쥬얼소진건취소
	const BYTE kPacketType_ConfirmJewelPurchase                         = 0xB7; //쥬얼소진건승인
	const BYTE kPacketType_TradeJewel                                   = 0xB8; //쥬얼경매장거래
	const BYTE kPacketType_CheckTradeJewel                              = 0xB9; //쥬얼경매장거래건확인
	const BYTE kPacketType_CancelJewelTrade                             = 0xBA; //쥬얼경매장거래건취소
	const BYTE kPacketType_ConfirmJewelTrade                            = 0xBB; //쥬얼 경매장 거래건 승인
	const BYTE kPacketType_PickUpTradeJewel								= 0xBC; // 쥬얼 경매장 판매금액 수령(판매자)
	const BYTE kPacketType_CheckTradeJewelPickUp						= 0xBD; // 경매장 판매금액 수령건 확인
	const BYTE kPacketType_CancelTradeJewelPickUp						= 0xBE; // 경매장 판매금액 수령건 취소
	const BYTE kPacketType_ConfirmTradeJewelPickUp						= 0xBF; // 경매장 판매금액 수령건 승인
	
	// Advanced Billing - Cash Inventory
	const BYTE kPacketType_InquiryCashInventory							= 0x69; //캐시인벤토리조회
	const BYTE kPacketType_InquiryCashInventoryByBindAttribute			= 0x81; //아이템 귀속 형태에 따른 캐시인벤토리조회
	const BYTE kPacketType_PickupCashInventoryItem						= 0x6B; //캐시인벤토리수령
	const BYTE kPacketType_PickupCashInventoryItemByBindAttribute		= 0x82; //아이템 귀속 형태에 따른 캐시인벤토리수령
	const BYTE kPacketType_CancelCashInventoryItem						= 0x6C; //캐시인벤토리복구
	const BYTE kPacketType_CancelCashInventoryItemByBindAttribute		= 0x83; //아이템 귀속 형태에 따른 캐시인벤토리복구
	const BYTE kPacketType_PickupCashSubInventoryItem					= 0x6D; //개별캐시인벤토리수령
	const BYTE kPacketType_PickupCashSubInventoryItemByBindAttribute	= 0x84; //아이템 귀속 형태에 따른 개별캐시인벤토리수령
	const BYTE kPacketType_CancelCashSubInventoryItem					= 0x6E; //개별캐시인벤토리취소
	const BYTE kPacketType_CancelCashSubInventoryItemByBindAttribute	= 0x85; //아이템 귀속 형태에 따른 개별캐시인벤토리취소
	const BYTE kPacketType_InquiryPickupStandbyCashPurchaseNo			= 0x86;	//게임에서 수령가능한 아이템 구매번호 리스트 조회
	const BYTE kPacketType_PickupStandbyCashInventory					= 0x87;	//구매 번호에 해당하는 아이템을 게임 내 수령 대기상태로 전환
	const BYTE kPacketType_CompletePickupStandbyCashInventory			= 0x8C;	//구매 번호에 해당하는 아이템을 게임 내 수령 완료상태로 전환
	const BYTE kPacketType_CancelPickupStandbyCashInventory				= 0x8D;	//구매 번호에 해당하는 아이템을 게임 내 수령 대기상태에서 취소
	const BYTE kPacketType_UseStorage									= 0x8E; //IBS 보관함 상품 사용
	const BYTE kPacketType_RollbackUseStorage							= 0x8F; //IBS 보관함 사용 롤백
	// Advanced Billing - Inquiry OData
	const BYTE kPacketType_InquiryServiceMetadata						= 0x74; //서비스메타데이타조회
	const BYTE kPacketType_InquiryODataService							= 0x75; //OData서비스조회
	// Advanced Billing - Cart & Wish Items
	const BYTE kPacketType_InquiryCartItems								= 0xA1; //쇼핑카트아이템조회
	const BYTE kPacketType_RegisterCartItems							= 0xA2; //쇼핑카트아이템등록
	const BYTE kPacketType_ModifyCartItemsQuantity						= 0xA3; //쇼핑카트아이템수량변경
	const BYTE kPacketType_ModifyCartItemsAttribute						= 0xA4; //쇼핑카트아이템속성변경
	const BYTE kPacketType_RemoveCartItems								= 0xA5; //쇼핑카트아이템삭제
	const BYTE kPacketType_RemoveCart									= 0xA6; //쇼핑카트전체아이템삭제
	const BYTE kPacketType_CartItemsTransferWishItems					= 0xA7; //위시아이템으로쇼핑카트아이템이동
	const BYTE kPacketType_InquiryWishItems								= 0xAB; //위시아이템조회
	const BYTE kPacketType_RegisterWishItems							= 0xAC; //위시아이템등록
	const BYTE kPacketType_RemoveWishItems								= 0xAD; //위시아이템삭제
	const BYTE kPacketType_RemoveWish									= 0xAE; //위시아이템전체삭제
	const BYTE kPacketType_WishItemsTransferCartItems					= 0xAF; //쇼핑카트아이템으로위시아이템이동
	// Advanced Billing - Order
	const BYTE kPacketType_ShopDirectPurchaseItem						= 0xC9; //바로구매
	const BYTE kPacketType_ShopDirectPurchaseItemByBindAttribute		= 0x88; //아이템 귀속 형태에 따른 바로구매
	const BYTE kPacketType_ShopPurchaseCartItems						= 0xCA; //쇼핑카트아이템구매
	const BYTE kPacketType_ShopDirectGiftItem							= 0xCB; //바로선물하기
	const BYTE kPacketType_ShopDirectGiftItemByBindAttribute			= 0x89; //아이템 귀속 형태에 따른 바로선물하기
	const BYTE kPacketType_ShopGiftCartItems							= 0xCC; //쇼핑카트아이템선물
	// Advanced Billing - Coupon									
	const BYTE kPacketType_CheckCoupon									= 0xDD; //쿠폰조회
	const BYTE kPacketType_CheckCouponByBindAttribute					= 0x8A; //아이템 귀속 형태에 따른 쿠폰조회
	const BYTE kPacketType_UseCoupon									= 0xDE; //쿠폰사용
	const BYTE kPacketType_UseCouponByBindAttribute						= 0x8B; //아이템 귀속 형태에 따른 쿠폰사용


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 2 Result Codes
	//	시스템메시지규칙
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
	const INT32 kRCSuccess			= 1;				//성공
	const INT32 kRCFailure			= 2;				//실패
	const INT32 kRCException		= 3;				//오류
	const INT32 kRCNoResult			= 4;				//(2-Phase Commit) 구매, 충전, 픽업, 소진에 대한 트랜잭션 조회 시 결과 없음
	const INT32 kRCFailureTransactionalOperation = 5;	//(2-Phase Commit) 구매, 충전, 픽업, 소진에 대한 승인 및 취소에 대한 트랜잭션 동작 실패 시
	const INT32 kRCFCSAdapterError	= 9;	 //FCS Adapter Error

	const INT32 kRC90001			= 90001; //Parameter오류
	const INT32 kRC90002			= 90002; //해당레코드없음
	const INT32 kRC90003			= 90003; //이력등록오류
	const INT32 kRC90004			= 90004; //중복등록오류
	const INT32 kRC90005			= 90005; //지정한데이터가잘못되었습니다.
	const INT32 kRC90006			= 90006; //유효하지않은1차카테고리임
	const INT32 kRC90007			= 90007; //유효하지않은2차카테고리임
	const INT32 kRC90008			= 90008; //사용불가언어임
	const INT32 kRC90009			= 90009; //금칙어 일괄등록 실패
	const INT32 kRC90010			= 90010; //유효하지 않은 상태값

	const INT32 kRC90101			= 90101; //Userid중복오류
	const INT32 kRC90102			= 90102; //Email중복오류
	const INT32 kRC90103			= 90103; //사용자상태변경오류
	const INT32 kRC90104			= 90104; //보안유형변경오류
	const INT32 kRC90105			= 90105; //사용자데이터없음
	const INT32 kRC90106			= 90106; //비밀번호확인오류
	const INT32 kRC90107			= 90107; //등록되지않은SNS계정임
	const INT32 kRC90108			= 90108; //사용자등록실패
	const INT32 kRC90109			= 90109; //사용자프로필등록실패
	const INT32 kRC90110			= 90110; //사용자등급등록실패
	const INT32 kRC90111			= 90111; //SNS계정등록실패
	const INT32 kRC90112			= 90112; //프로필변경불가(레코드없거나비공개상태임)
	const INT32 kRC90113			= 90113; //이미등록된SNS계정정보가있음
	const INT32 kRC90114			= 90114; //사용중인SNS계정임
	const INT32 kRC90115			= 90115; //SNS계정이일치하지않음
	const INT32 kRC90116			= 90116; //Email변경실패
	const INT32 kRC90117			= 90117; //Nickname생성실패
	const INT32 kRC90118			= 90118; //SNS계정상태변경오류
	const INT32 kRC90119			= 90119; //Nickname상태변경오류
	const INT32 kRC90120			= 90120; //Nickname중복오류
	const INT32 kRC90121			= 90121; //Nickname등록중
	const INT32 kRC90122			= 90122; //Nickname생성및변경완료처리실패
	const INT32 kRC90123			= 90123; //이미인증처리된email임
	const INT32 kRC90124			= 90124; //사용자의상태는해당작업수행불가임
	const INT32 kRC90125			= 90125; //빌더그룹계정접두어중복오류
	const INT32 kRC90126			= 90126; //UserID길이에러
	const INT32 kRC90127			= 90127; //Password길이에러
	const INT32 kRC90128			= 90128; //Email길이에러
	const INT32 kRC90129			= 90129; //인증메일발송오류
	const INT32 kRC90130			= 90130; //SNS연결정보없음
	const INT32 kRC90131			= 90131; //동일패스워드
	const INT32 kRC90132			= 90132; //계정 생성 path등록 오류

	const INT32 kRC90201			= 90201; //인증키발행내역이없음
	const INT32 kRC90202			= 90202; //인증키기한만료
	const INT32 kRC90203			= 90203; //폐기된인증키임
	const INT32 kRC90204			= 90204; //Key상태변경오류
	const INT32 kRC90205			= 90205; //Key값오류
	const INT32 kRC90206			= 90206; //게임이용약관동의필요
	const INT32 kRC90207			= 90207; //SC사용선택중복오류
	const INT32 kRC90208			= 90208; //게임이용약관중복동의
	const INT32 kRC90209			= 90209; //사용가능요금제없음
	const INT32 kRC90210			= 90210; //요금제중복등록오류
	const INT32 kRC90211			= 90211; //로그인실패회수초과
	const INT32 kRC90212			= 90212; //인증키발급실패
	const INT32 kRC90213			= 90213; //유효하지않은인증키
	const INT32 kRC90214			= 90214; //인증키정보불일치
	const INT32 kRC90215			= 90215; //사용중인요금제없음
	const INT32 kRC90216			= 90216; //이미비활성화(중지)처리되었음
	const INT32 kRC90217			= 90217; //접속불가상태의사용자임
	const INT32 kRC90222			= 90222; //정의되지 않은 에러(인증 DB)

	const INT32 kRC90301			= 90301; //정책번호오류
	const INT32 kRC90302			= 90302; //정책기준번호오류
	const INT32 kRC90303			= 90303; //정의된정책없음
	const INT32 kRC90304			= 90304; //이미정의된정책임
	const INT32 kRC90305			= 90305; //포털접속불가계정
	const INT32 kRC90306			= 90306; //포털접속불가국가
	const INT32 kRC90307			= 90307; //요청한사용자의국가에서는충전할수없는PG
	const INT32 kRC90308			= 90308; //요청한사용자의빌링등급으로는충전할수없는PG
	const INT32 kRC90309			= 90309; //사용자빌링등급별월보유한도초과
	const INT32 kRC90310			= 90310; //사용자빌링등급별월충전한도초과
	const INT32 kRC90311			= 90311; //대상사용자정보오류
	const INT32 kRC90312			= 90312; //동일정책적용되어져있음
	const INT32 kRC90313			= 90313; //종료일이시작일이전입니다.
	const INT32 kRC90314			= 90314; //정책만료처리실패
	const INT32 kRC90315			= 90315; //사용자접속제한만료처리실패
	const INT32 kRC90316			= 90316; //접속 불가 채널링
	const INT32 kRC90317			= 90317; //요청한 채널링에서는 충전할 수 없는 PG
	const INT32 kRC90318			= 90318; //접속 불가 PII
	const INT32 kRC90319			= 90319; //연령제한으로 인한 게임 실행 불가
	const INT32 kRC90320			= 90320; //정상 상태의 계정임(해당 게임에 대해)
	const INT32 kRC90321			= 90321; //인증되지 않은 IP
	const INT32 kRC90322			= 90322; //등록되지 않은 서비스 코드

	const INT32 kRC90401			= 90401; //서비스별컨텐츠그룹중복오류
	const INT32 kRC90402			= 90402; //서비스별컨텐츠그룹분류중복오류
	const INT32 kRC90403			= 90403; //해당컨텐츠그룹없음
	const INT32 kRC90404			= 90404; //미디어게시물이없음
	const INT32 kRC90405			= 90405; //미디어의해당이미지사이즈파일중복오류
	const INT32 kRC90406			= 90406; //해당컨텐츠그룹분류없음
	const INT32 kRC90407			= 90407; //게시글수/댓글수/조회수수정오류
	const INT32 kRC90408			= 90408; //댓글등록불가컨텐츠임
	const INT32 kRC90409			= 90409; //댓글등록실패
	const INT32 kRC90410			= 90410; //게임실행정보중복오류
	const INT32 kRC90411			= 90411; //CDN파트너정보입력필요
	const INT32 kRC90412			= 90412; //다운로드서버유형정보입력필요
	const INT32 kRC90413			= 90413; //대륙정보입력필요
	const INT32 kRC90414			= 90414; //다운로드파일유형지정오류
	const INT32 kRC90415			= 90415; //다국어 맵핑 등록 오류
	const INT32 kRC90416			= 90416; //등록 개수 초과

	const INT32 kRC90501			= 90501; //EM등록오류
	const INT32 kRC90502			= 90502; //EM상태변경오류
	const INT32 kRC90503			= 90503; //EM대상중복등록오류
	const INT32 kRC90504			= 90504; //EM대상등록오류
	const INT32 kRC90505			= 90505; //EM대상상태변경오류
	const INT32 kRC90506			= 90506; //EM전송시점중복오류

	const INT32 kRC90601			= 90601; //FAQ등록오류
	const INT32 kRC90602			= 90602; //FAQ정보변경오류(상태변경포함)
	const INT32 kRC90603			= 90603; //FAQ조회수,LIKE수증가처리오류
	const INT32 kRC90604			= 90604; //사용자의1:1문의등록오류
	const INT32 kRC90605			= 90605; //사용자의1:1문의담당자지정(변경)오류
	const INT32 kRC90606			= 90606; //사용자의1:1문의상태변경오류
	const INT32 kRC90607			= 90607; //사용자의1:1문의답변등록오류
	const INT32 kRC90608			= 90608; //사용자의1:1문의답변변경오류(상태변경포함)
	const INT32 kRC90609			= 90609; //사용자의1:1문의첨부파일중복오류
	const INT32 kRC90610			= 90610; //티켓이 아님 (check)
	const INT32 kRC90611			= 90611; //티켓 서비스 Fault Exception (check)
	const INT32 kRC90612			= 90612; //티켓 서비스 Exception (check)
	const INT32 kRC90613			= 90613; //티켓이 아님 (use)
	const INT32 kRC90614			= 90614; //티켓 서비스 Fault Exception (use)
	const INT32 kRC90615			= 90615; //티켓 서비스 Exception (use)
	const INT32 kRC90616			= 90616; //담당 관리자가 아님
	const INT32 kRC90617			= 90617; //처리불가 문의사항임
	const INT32 kRC90618			= 90618; //해당 사용자의 문의사항이 아님
	const INT32 kRC90619			= 90619; //다국어 맵핑 등록 오류
	const INT32 kRC90620			= 90620; //덧글 등록 불가 대상(사용자/cs담당자)임
	const INT32 kRC90621			= 90621; //카테고리와 서브 카테고리 매핑 오류

	const INT32 kRC90701			= 90701; //빌링사용자등록오류
	const INT32 kRC90702			= 90702; //빌링사용자정보변경오류
	const INT32 kRC90703			= 90703; //충전수단중복등록오류
	const INT32 kRC90704			= 90704; //충전수단등록오류
	const INT32 kRC90705			= 90705; //충전수단정보변경오류
	const INT32 kRC90706			= 90706; //충전상품중복등록오류
	const INT32 kRC90707			= 90707; //충전상품등록오류
	const INT32 kRC90708			= 90708; //충전상품정보변경오류
	const INT32 kRC90709			= 90709; //판매아이템중복등록오류
	const INT32 kRC90710			= 90710; //판매아이템등록오류
	const INT32 kRC90711			= 90711; //판매아이템정보변경오류
	const INT32 kRC90712			= 90712; //충전요청중복등록오류
	const INT32 kRC90713			= 90713; //충전요청등록오류
	const INT32 kRC90714			= 90714; //충전확인처리오류
	const INT32 kRC90715			= 90715; //충전완료처리오류
	const INT32 kRC90716			= 90716; //충전실패처리오류
	const INT32 kRC90717			= 90717; //결제트랜잭션중복등록오류
	const INT32 kRC90718			= 90718; //결제트랜잭션등록오류
	const INT32 kRC90719			= 90719; //잔액중복등록오류
	const INT32 kRC90720			= 90720; //잔액등록오류
	const INT32 kRC90721			= 90721; //잔액증감처리오류
	const INT32 kRC90722			= 90722; //PGhandshaking오류
	const INT32 kRC90726			= 90726; //장바구니중복등록오류
	const INT32 kRC90727			= 90727; //장바구니등록오류
	const INT32 kRC90728			= 90728; //PGStartToken조회실패
	const INT32 kRC90729			= 90729; //구매상태변경오류
	const INT32 kRC90730			= 90730; //구매처리실패
	const INT32 kRC90731			= 90731; //구매처리중잔액부족오류
	const INT32 kRC90732			= 90732; //구매등록오류
	const INT32 kRC90733			= 90733; //구매취소처리오류
	const INT32 kRC90734			= 90734; //환불이안되는결제수단
	const INT32 kRC90735			= 90735; //환불중복등록오류
	const INT32 kRC90736			= 90736; //환불등록오류
	const INT32 kRC90737			= 90737; //환불처리오류
	const INT32 kRC90738			= 90738; //코인 쿠폰이 아님 (check)
	const INT32 kRC90739			= 90739; //쿠폰 서비스 Fault Exception (check)
	const INT32 kRC90740			= 90740; //쿠폰 서비스 Exception (check)
	const INT32 kRC90741			= 90741; //코인 쿠폰이 아님 (use)
	const INT32 kRC90742			= 90742; //쿠폰 서비스 Fault Exception (use)
	const INT32 kRC90743			= 90743; //쿠폰 서비스 Exception (use)
	const INT32 kRC90744			= 90744; //애플 결제 확인 성공 했으나 충전 상품에는 없음
	const INT32 kRC90745			= 90745; //애플 결제 확인 재시도 결과 성공 했으나 충전 상품에는 없음
	const INT32 kRC90746			= 90746; //애플 결제 확인 재시도 결과도 실패
	const INT32 kRC90747			= 90747; //애플 결제 확인 재시도 Exception
	const INT32 kRC90748			= 90748; //애플 결제 확인 실패
	const INT32 kRC90749			= 90749; //애플 결제 확인 Exception
	const INT32 kRC90750			= 90750; //구글 결제 확인 실패
	const INT32 kRC90751			= 90751; //환불 안되는 충전건 (소진건이 존재함)
	const INT32 kRC90752			= 90752; //SKT 결제 확인 실패
	const INT32 kRC90753			= 90753; //SKT 결제 확인 실패 (상세 실패)
	const INT32 kRC90754			= 90754; //SKT 결제 확인 성공 했으나 충전 상품에는 없음
	const INT32 kRC90755			= 90755; //SKT 결제 확인 Exception
	const INT32 kRC90756			= 90756; //구매 횟수 초과
	const INT32 kRC90757			= 90757; //판매 수량 초과
	const INT32 kRC90758			= 90758; //첫 유료 구매 불가
	const INT32 kRC90759			= 90759; //구매 제한 설정값 오류
	const INT32 kRC90760			= 90760; //구글 결제확인 Exception
	const INT32 kRC90761			= 90761; //캐시사용제한

	const INT32 kRC90801			= 90801; //유효하지않은프로모션
	const INT32 kRC90802			= 90802; //유효하지않은프로모션파트너
	const INT32 kRC90803			= 90803; //유효하지않은쿠폰유형
	const INT32 kRC90804			= 90804; //유효하지않은쿠폰그룹
	const INT32 kRC90805			= 90805; //유효하지않은쿠폰상품
	const INT32 kRC90806			= 90806; //쿠폰그룹상품추가불가
	const INT32 kRC90807			= 90807; //속성설정오류
	const INT32 kRC90808			= 90808; //속성플래그설정오류
	const INT32 kRC90809			= 90809; //발행매수오류
	const INT32 kRC90810			= 90810; //쿠폰구성정보수정오류
	const INT32 kRC90811			= 90811; //유효하지않은serial
	const INT32 kRC90812			= 90812; //쿠폰사용불가대상임
	const INT32 kRC90813			= 90813; //사용가능개수초과
	const INT32 kRC90814			= 90814; //사용처리등록오류
	const INT32 kRC90815			= 90815; //참여결과등록오류
	const INT32 kRC90816			= 90816; //이미사용된쿠폰임
	const INT32 kRC90817			= 90817; //사용초기화된쿠폰임
	const INT32 kRC90818			= 90818; //쿠폰그룹상품없음
	const INT32 kRC90819			= 90819; //프로모션상태변경오류
	const INT32 kRC90820			= 90820; //프로모션파트너상태변경오류
	const INT32 kRC90821			= 90821; //쿠폰그룹상태변경오류
	const INT32 kRC90822			= 90822; //쿠폰그룹상품상태변경오류
	const INT32 kRC90823			= 90823; //프로모션파트너contracttype변경오류
	const INT32 kRC90824			= 90824; //period변경오류
	const INT32 kRC90825			= 90825; //유효하지않은쿠폰그룹정보
	const INT32 kRC90826			= 90826; //유효하지않은쿠폰그룹상품
	const INT32 kRC90827			= 90827; //유효하지않은속성
	const INT32 kRC90828			= 90828; //요청 트랜잭션 중복 등록 오류
	const INT32 kRC90829			= 90829; //유효하지 않은 계약 유형
	const INT32 kRC90830			= 90830; //발행 가능 쿠폰 매수 부족
	const INT32 kRC90831			= 90831; //발행 정보 수정 오류
	const INT32 kRC90832			= 90832; //속성 설정 불가 (사용된 쿠폰이 있는 경우)

	const INT32 kRC90901			= 90901; //할인정보입력오류
	const INT32 kRC90902			= 90902; //유효하지않은아이템
	const INT32 kRC90903			= 90903; //기간정보입력오류
	const INT32 kRC90904			= 90904; //판매속성정보입력오류
	const INT32 kRC90905			= 90905; //샵사용자정보오류
	const INT32 kRC90906			= 90906; //중복된아이템판매정보임
	const INT32 kRC90907			= 90907; //위시리스트에이미존재함
	const INT32 kRC90908			= 90908; //유효하지않은구매요청정보임
	const INT32 kRC90909			= 90909; //유효하지않은구매인벤토리정보
	const INT32 kRC90910			= 90910; //아이템수령오류
	const INT32 kRC90911			= 90911; //아이템가격오류
	const INT32 kRC90912			= 90912; //아이템구매가능레벨이나성별불일치
	const INT32 kRC90913			= 90913; //아이템구매한도초과
	const INT32 kRC90914			= 90914; //해당아이템구매불가사용자임
	const INT32 kRC90915			= 90915; //판매잔여수량부족
	const INT32 kRC90916			= 90916; //1회구매가능수량오류
	const INT32 kRC90917			= 90917; //재구매제한오류
	const INT32 kRC90918			= 90918; //구매인벤토리등록실패
	const INT32 kRC90919			= 90919; //묶은아이템인벤토리등록실패
	const INT32 kRC90920			= 90920; //복권아이템인벤토리등록실패
	const INT32 kRC90921			= 90921; //보너스아이템인벤토리등록실패
	const INT32 kRC90922			= 90922; //구매인벤토리정보오류
	const INT32 kRC90923			= 90923; //수령가능아이템이없음
	const INT32 kRC90924			= 90924; //유효하지않은카테고리
	const INT32 kRC90925			= 90925; //유효하지않은서비스
	const INT32 kRC90926			= 90926; //카트정보수정오류
	const INT32 kRC90927			= 90927; //등록대상아이템이없음
	const INT32 kRC90928			= 90928; //부모(패키지/복권/보너스)아이템정보오류
	const INT32 kRC90929			= 90929; //멤버아이템정보오류
	const INT32 kRC90930			= 90930; //충전캐시유형설정오류
	const INT32 kRC90931			= 90931; //부모아이템의판매유형설정오류
	const INT32 kRC90932			= 90932; //수령수량오류
	const INT32 kRC90933			= 90933; //소령로그기록실패
	const INT32 kRC90934			= 90934; //구매인벤토리수령실패
	const INT32 kRC90935			= 90935; //묶은아이템인벤토리수령실패
	const INT32 kRC90936			= 90936; //복권아이템인벤토리수령실패
	const INT32 kRC90937			= 90937; //보너스아이템인벤토리수령실패
	const INT32 kRC90938			= 90938; //멤버아이템중복등록오류
	const INT32 kRC90939			= 90939; //복권비율설정오류
	const INT32 kRC90940			= 90940; //할인기간중복오류
	const INT32 kRC90941			= 90941; //유효하지않은게임서버정보
	const INT32 kRC90942			= 90942; //유효하지않은카드정보
	const INT32 kRC90943			= 90943; //선물불가아이템임
	const INT32 kRC90944			= 90944; //변경 불가 항목 수정 오류
	const INT32 kRC90945			= 90945; //판매 캐시 유형 설정 오류
	const INT32 kRC90946			= 90946; //아이템 보너스 여부 설정 변경 실패
	const INT32 kRC90947			= 90947; //아이템 쿠폰이 아님 (check)
	const INT32 kRC90948			= 90948; //아이템 정보 조회 오류 (check)
	const INT32 kRC90949			= 90949; //아이템 정보 찾을 수 없음 (check)
	const INT32 kRC90950			= 90950; //쿠폰 서비스 Fault Exception (check)
	const INT32 kRC90951			= 90951; //쿠폰 서비스 Exception (check)
	const INT32 kRC90952			= 90952; //아이템 쿠폰이 아님 (use)
	const INT32 kRC90953			= 90953; //쿠폰 서비스 Fault Exception (use)
	const INT32 kRC90954			= 90954; //쿠폰 서비스 Exception (use)
	const INT32 kRC90955			= 90955; //부모 카테고리 설정 오류
	const INT32 kRC90956			= 90956; //아이템을 가질 수 없는 카테고리임
	const INT32 kRC90957			= 90957; //변경 불가 아이템 판매 정보임
	const INT32 kRC90958			= 90958; //개별/일괄 수령 불가능함
	const INT32 kRC90959			= 90959; //아이템 쿠폰 사용 불가
	const INT32 kRC90960			= 90960; //카트/위시리스트 보관 최대 개수 초과
	const INT32 kRC90961			= 90961; //카트/위시리스트 사용 불가 게임임
	const INT32 kRC90962			= 90962; //유효하지 않은 아이템 정의
	const INT32 kRC90963			= 90963; //WCoin 충전 아이템 설정 개수 오류
	const INT32 kRC90964			= 90964; //패키지 구성시, 복권 설정 불가
	const INT32 kRC90965			= 90965; //패키지/복권 구성시, 다른 패키지 혹은 보너스 설정 아이템 설정 불가
	const INT32 kRC90966			= 90966; //일괄 지급 계정 관련 정보 오류
	const INT32 kRC90967			= 90967; //일괄 지급 게임 관련 정보 오류
	const INT32 kRC90968			= 90968; //구매 금액 불일치
	const INT32 kRC90969			= 90969; //주문번호 중복
	const INT32 kRC90970			= 90970; //구매 철회시 대상 아이템 없음
	const INT32 kRC90971			= 90971; //채널링키를 통한 사용자 정보 취득 실패
	const INT32 kRC90972			= 90972; //구매 제한 회수 오류

	const INT32 kRC91101			= 91101; //유효하지 않은 GameCode 임
	const INT32 kRC91102			= 91102; //IP 확인 오류

	const INT32 kRC91201			= 91201; //아이템 등록 오류
	const INT32 kRC91202			= 91202; //2.0 아이템 동기화 오류

	const INT32 kRC91301			= 91301; //유효하지 않은 채널링 파트너사임
	const INT32 kRC91302			= 91302; //채널링 사용자 기본 정보 등록 오류
	const INT32 kRC91303			= 91303; //채널링 사용자 설정 등록 오류
	const INT32 kRC91304			= 91304; //채널링 사용자 설정 상세 등록 오류
	const INT32 kRC91305			= 91305; //유효하지 않은 채널링 계정 정보
	const INT32 kRC91306			= 91306; //유효하지 않은 채널링 파트너 계정 정보
	const INT32 kRC91307			= 91307; //이미 채널링 등록된 계정임
	const INT32 kRC91308			= 91308; //채널링 정보 없음
	const INT32 kRC91309			= 91309; //채널링 해제 실패
	const INT32 kRC91310			= 91310; //다른 채널링 파트너사에 등록된 계정임

	const INT32 kRC91401			= 91401; //이미 발송 되었음

	const INT32 kRC91501			= 91501; //퍼블리셔 API 연동 실패
	const INT32 kRC91502			= 91502; //퍼블리셔 비즈 오류


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 3 Condition Types
	const BYTE kCT_None       					 	= 0x00; //기본값         
	const BYTE kCT_ConflictConfigurationVersion		= 0x14; //설정정보 변경됨
	const BYTE kCT_ConflictProductVersion			= 0x15; //상품정보 변경됨
	const BYTE kCT_Running                          = 0x64; //서버 정상 가동 
	const BYTE kCT_Stop                             = 0x65; //서버 중지      
	const BYTE kCT_Maintenance                      = 0xFF; //점검 중        


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 4 Return Structure Types
	const BYTE kRST_Default	    = 0x00; //기본                           
	const BYTE kRST_XML         = 0x01; //XML Type                       
	const BYTE kRST_JSON        = 0x02; //JSON Type(http://www.json.org/)
	const BYTE kRST_Exclusion   = 0xFF; //Return Structure 제외                                 


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 5 Sales Types
	const BYTE kST_None					= 0x00; //정의되지 않음                 
	const BYTE kST_CCoin				= 0x01; //C Coin (System Code: TRT001)
	const BYTE kST_PCoin				= 0x02; //P Coin (System Code: TRT002)
	const BYTE kST_ComplexCoin			= 0x03; //C+P Coin (System Code: TRT011)
	const BYTE kST_FlatRate				= 0x04; //P Coin 정액 (System Code: TRT022)
	const BYTE kST_ETC					= 0x05; //기타 (System Code: TRT005)
	const BYTE kST_CCoinFlatRate		= 0x06; //C Coin정액(System Code: TRT002)
	const BYTE kST_ComplexCoinFlatRate	= 0x07; //C+P Coin 정액(System Code: TRT012)
                                                                            

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 6 Authorization Use Status Type
	const wchar_t kSTS210[7] = L"STS210";	//Activation 전                                   
	const wchar_t kSTS211[7] = L"STS211";	//Activation 후                                   
	const wchar_t kSTS212[7] = L"STS212";	//사용 중                                         
	const wchar_t kSTS213[7] = L"STS213";	//사용중지(관리자에 의한)                         
	const wchar_t kSTS214[7] = L"STS214";	//사용중지(충전 환불에 의한 취소)                 
	const wchar_t kSTS215[7] = L"STS215";	//사용중지(충전 환불에 의한 부분취소)             
	const wchar_t kSTS216[7] = L"STS216";	//사용만료(사용기간 경과)                         
	const wchar_t kSTS217[7] = L"STS217";	//사용만료(사용 만료 후 충전 환불에 의한 취소)    
	const wchar_t kSTS218[7] = L"STS218";	//사용만료(사용 만료 후 충전 환불에 의한 부분취소)
	const wchar_t kSTS219[7] = L"STS219";	//사용만료(활성화 유효기간 경과)                  


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 7 Authorization User Type (1.2.2 스펙에서 변경됨)
	const wchar_t kSUT001[7] = L"SUT001";	//일반 사용자
	const wchar_t kSUT002[7] = L"SUT002";	//GM
	const wchar_t kSUT003[7] = L"SUT003";	//Tester

	//const wchar_t kUST001[7] = L"UST001";	//일반 사용자
	//const wchar_t kUST002[7] = L"UST002";	//웹 관리자  
	//const wchar_t kUST003[7] = L"UST003";	//GM         
	//const wchar_t kUST004[7] = L"UST004";	//QA         
	//const wchar_t kUST005[7] = L"UST005";	//Partner    
	//const wchar_t kUST006[7] = L"UST006";	//Tester     
                                                                         
	/////////////////////////////////////////////////////////////////////////////////////
	// Table 8 Authorization User Status
	const wchar_t kSTS120[7] = L"STS120";	//가입신청(대기)
	const wchar_t kSTS121[7] = L"STS121";	//인증완료(정상)
	const wchar_t kSTS122[7] = L"STS122";	//제재 중       
	const wchar_t kSTS123[7] = L"STS123";	//탈퇴          
	const wchar_t kSTS124[7] = L"STS124";	//강제탈퇴      
	const wchar_t kSTS125[7] = L"STS125";	//관리 중       

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 9 Authorization Security Provider Type
	const wchar_t kSCT001[7] = L"SCT001";		//일반사용자
	const wchar_t kSCT002[7] = L"SCT002";		//SC카드 사용

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 10 Data Types
	//	N/A

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 11 Inquiry Cash Inventory Expand Flags
	const BYTE kICIEF_Purchase	= 0x00; //주문 아이템
	const BYTE kICIEF_Package	= 0x01; //패키지 아이템
	const BYTE kICIEF_Lottery	= 0x02; //복권 아이템
	const BYTE kICIEF_Bonus		= 0x04; //보너스 아이템
	const BYTE kICIEF_All		= 0x07; //전체 (Order | Package | Lottery | Bonus)

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 12 Inquiry Item Status Flags
	const INT32 kIISF_Disabled	= -1;	//판매중지 아이템
	const INT32 kIISF_Enabled	= 0x00; //판매 아이템
	const INT32 kIISF_New		= 0x01; //신규 아이템
	const INT32 kIISF_Event		= 0x02; //이벤트 아이템
	const INT32 kIISF_Limited	= 0x04; //한정 아이템
	const INT32 kIISF_Hot		= 0x08; //인기 아이템
	const INT32 kIISF_Best		= 0x10; //베스트 아이템
	const INT32 kIISF_Reserved	= 0x20; //예약 아이템
	const INT32 kIISF_Sales		= 0x40; //할인 아이템
	const INT32 kIISF_All		= 0x7F; //전체 (Enabled | New | Event | Limited | Hot | Best | Reserved | Sales)

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 13 Inquiry Item Order by Type
	const BYTE kIIOBT_Default				= 0; //정렬 기본 값
	const BYTE kIIOBT_ItemNameAscending		= 1; //아이템 이름 순
	const BYTE kIIOBT_ItemNameDescending	= 2; //아이템 이름 역순
	const BYTE kIIOBT_ItemAmountAscending	= 3; //최저 가격
	const BYTE kIIOBT_ItemAmountDescending	= 4; //최고 가격


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 14 Inquiry Expand Flags
	const INT32 kIEF_MainItems				= 0x00; //기본 아이템
	const INT32 kIEF_PackageItems			= 0x01; //패키지 아이템
	const INT32 kIEF_LotteryItems			= 0x02; //복권 아이템
	const INT32 kIEF_LinkageItems			= 0x04; //연관 아이템
	const INT32 kIEF_RecommendationItems	= 0x08; //추천 아이템
	const INT32 kIEF_BonusItems				= 0x10; //보너스 아이템
	const INT32 kIEF_ItemProperties			= 0x20; //아이템 속성


	/////////////////////////////////////////////////////////////////////////////////////
	// Table 15 Inquiry Cart & Wish Expand Flags
	const INT32 kICWEF_Default			= 0x00; //쇼핑카트 또는 위시아이템
	const INT32 kICWEF_ItemProperties	= 0x01; //아이템 속성
	const INT32 kICWEF_LinkageItems		= 0x02; //연관 아이템
	const INT32 kICWEF_All				= 0x03; //전체 (Default | Properties | Linkage)
	
	/////////////////////////////////////////////////////////////////////////////////////
	// Table 16 Execute Method Type
	const BYTE kEMT_Discounts			= 0x00; //할인정보조회
	const BYTE kEMT_GameWorlds			= 0x01; //게임월드에대한기본정보
	const BYTE kEMT_Categories			= 0x02; //카테고리기본정보
	const BYTE kEMT_Properties			= 0x03; //속성기본정보
	const BYTE kEMT_Tags				= 0x04; //태그기본정보
	const BYTE kEMT_CategoryWorlds		= 0x05; //게임월드에연결된카테고리정보
	const BYTE kEMT_ProductCategories	= 0x06; //카테고리에연결된아이템정보
	const BYTE kEMT_ProductProperties	= 0x07; //상품에연결된속성정보
	const BYTE kEMT_ProductTags			= 0x08; //상품에연결된태그정보
	const BYTE kEMT_Products			= 0x09; //상품기본정보
	const BYTE kEMT_ProductSales		= 0x0A; //상품판매정보
	const BYTE kEMT_ProductPackages		= 0x0B; //상품에연결된패키지정보
	const BYTE kEMT_ProductLotteries	= 0x0C; //상품에연결된복권정보
	const BYTE kEMT_ProductBonuses		= 0x0D; //상품에연결된보너스정보
	const BYTE kEMT_ProductLinkage		= 0x0E; //상품에연결된연관상품정보
	const BYTE kEMT_ProductRecommends	= 0x0F; //상품에연결된추천상품

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 18 Cash Type
	enum saleCoinType {
		kSCT_UNKNOWN = 0,
		kSCT_WCOIN = 1,												 // 웹젠 코인
		kSCT_REDGEN,												 // 레드젠
		kSCT_IMPUTATION_REDGEN										 // 귀속레드젠
	};
	
	/////////////////////////////////////////////////////////////////////////////////////
	// ETC. Receive Type : 받는 타입
	const BYTE kRTRequest			= 0x01; //요청수령
	const BYTE kRTAuto				= 0x02; //자동수령
	const BYTE kRTForce				= 0x03; //강제수령
	const BYTE kRTExpiredForce		= 0x04; //만료강제수령
	const BYTE kRTDelete			= 0x05; //삭제
	const BYTE kRTExpiredDelete		= 0x06; //만료삭제

	/////////////////////////////////////////////////////////////////////////////////////
	// ETC. Inventory Type : 인벤토리 타입
	const BYTE kITPackageInventories	= 0x01; //Package Inventories
	const BYTE kITLotteryInventories	= 0x02; //Lottery Inventories
	const BYTE kITBonusInventories		= 0x04; //Bonus Inventories

	/////////////////////////////////////////////////////////////////////////////////////
	// ETC. Inventory Status : 인벤토리 상태
	const BYTE kISImmediately	= 0x1F; //즉시수령
	const BYTE kISPickup		= 0x05; //픽업을 통한 수령

	/////////////////////////////////////////////////////////////////////////////////////
	// Table 25 Order Status
	enum orderStatus {
		kOS_NOT_ORDERED = 0,	// 주문 요청 안됨 (주문승인/취소 불가)
		kOS_ORDERED = 1,		// 주문 요청됨 (주문승인/취소 가능)
		kOS_CONFIRMED,			// 주문 승인됨 (주문취소 불가)
		kOS_CANCELED			// 주문 취소됨 (주문승인 불가)
	};


} // namespace

#endif
