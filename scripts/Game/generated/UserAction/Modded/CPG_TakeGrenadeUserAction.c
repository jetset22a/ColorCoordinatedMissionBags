class CPG_TakeGrenadeUserAction : CPG_TakeItemUserAction {
		
	override InventorySearchPredicate GetSearchPredicate(IEntity pOwnerEntity) {
		return SCR_ItemTypeSearchPredicate(GrenadeMoveComponent, 7, null);
	}
	
	override string GetItemName() {
		return "Grenade";
	}
}