#ifndef FCSADAPTER_INTERFACE_FCSADAPTER_H_
#define FCSADAPTER_INTERFACE_FCSADAPTER_H_


#if defined(FCSADAPTER_EXPORT)
	#define FCSADAPTER_EXTERN_TEMAPLTE template
	#define FCSADAPTER_DECLSPEC __declspec(dllexport)
	#define FCSADAPTER_API extern "C" __declspec(dllexport)
	//..
#else
	#define FCSADAPTER_EXTERN_TEMAPLTE extern template 
	#define FCSADAPTER_DECLSPEC __declspec( dllimport )
	#define FCSADAPTER_API extern "C" __declspec( dllimport )
	//..
#endif

#include "fcs_constant.h"
#include "fcs_adapter_interfaces.h"


namespace fcsa
{
	// FCSAdapter Manager Instance
	typedef bool		(*LPFN_Initialize)();
	typedef void		(*LPFN_Uninitialize)();
	typedef IManager*	(*LPFN_GetInstance)();
	//typedef IManager*	(*GetSingleManagerInstanceFunction)();

	FCSADAPTER_API bool			__cdecl Initialize();
	FCSADAPTER_API void			__cdecl Uninitialize();
	FCSADAPTER_API IManager*	__cdecl GetInstance();
	//FCSADAPTER_API IManager*	__cdecl getSingleManagerInstance();


//////////////////////////////////////////////////////////////////////////////////////////////////
// export template
#pragma warning(push)
#pragma warning(disable: 4231)
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IResponseFlatRatePaymentInfo*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IRequestItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IResponseApprovalItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IResponsePurchaseItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IPurchaseItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IPurchaseNo*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<ICashInventoryItems*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<ICartItemInfo*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IRegisterItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IRequestNo*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IWishItemInfo*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IApprovalItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<ICartItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<ICouponItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IPackageItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<ILotteryItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IBonusItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<ICashInventoryItemsByBindAttribute*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IPackageItemByBindAttribute*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<ILotteryItemByBindAttribute*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IBonusItemByBindAttribute*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IPickupStandbyCashInventoryItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<ISTItemProperty*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IJewelBalanceItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IPStrA*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IWShopRequestPurchaseItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IWShopResponseApproval*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IWShopRequestOrderId*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IWShopInventoryItem*>;
	FCSADAPTER_EXTERN_TEMAPLTE class FCSADAPTER_DECLSPEC IArrayPtr<IWShopPickUpItem*>;
	
#pragma warning(pop)

} // namespace

#endif
