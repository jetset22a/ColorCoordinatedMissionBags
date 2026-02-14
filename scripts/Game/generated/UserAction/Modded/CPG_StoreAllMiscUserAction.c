class CPG_StoreAllMiscUserAction : CPG_BaseStoreAllUserAction {
	override array<ECommonItemType> GetItemTypesToStore() {
		return {ECommonItemType.BINOCULARS, ECommonItemType.COMPASS, ECommonItemType.FLASHLIGHT, ECommonItemType.RADIO, ECommonItemType.WATCH, ECommonItemType.DETONATOR, ECommonItemType.GPS};
	}
}