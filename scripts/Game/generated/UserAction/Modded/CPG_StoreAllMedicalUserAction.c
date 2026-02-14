class CPG_StoreAllMedicalUserAction : CPG_BaseStoreAllUserAction {
	override array<ECommonItemType> GetItemTypesToStore() {
		return {ECommonItemType.BANDAGE, ECommonItemType.MORPHINE, ECommonItemType.TOURNIQUET, ECommonItemType.SALINE};
	}
}