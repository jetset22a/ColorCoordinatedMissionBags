class CPG_StoreAllMiscUserAction : CPG_BaseStoreAllUserAction {
	override array<string> GetProtectedStorageNames() {
		return {"SCR_CharacterInventoryStorageComponent", "SCR_EquipmentStorageComponent"};
	}
	
	override array<ECommonItemType> GetItemTypesToStore() {
		return {ECommonItemType.BINOCULARS, ECommonItemType.COMPASS, ECommonItemType.FLASHLIGHT, ECommonItemType.RADIO, ECommonItemType.WATCH, ECommonItemType.DETONATOR, ECommonItemType.GPS};
	}
}