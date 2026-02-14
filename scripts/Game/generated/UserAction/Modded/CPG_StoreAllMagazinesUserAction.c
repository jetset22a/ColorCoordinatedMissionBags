class CPG_StoreAllMagazinesUserAction : CPG_BaseStoreAllComponentUserAction {
	override array<string> GetProtectedStorageNames() {
		return {"SCR_WeaponAttachmentsStorageComponent"};
	}
	
	override array<typename> GetComponentTypeNameToStore() {
		return {MagazineComponent};
	}
}