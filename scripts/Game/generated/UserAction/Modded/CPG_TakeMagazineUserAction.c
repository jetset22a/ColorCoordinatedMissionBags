class CPG_TakeMagazineUserAction : CPG_TakeItemUserAction {
	ref SCR_MagazinePredicate magazinePredicate;
		
	override InventorySearchPredicate GetSearchPredicate(IEntity pOwnerEntity) {
		return magazinePredicate;
	}
	
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		SCR_CharacterInventoryStorageComponent userStorageComponent = SCR_CharacterInventoryStorageComponent.Cast(pUserEntity.FindComponent(SCR_CharacterInventoryStorageComponent));
		if(!userStorageComponent) {
			Print("SCR_CharacterInventoryStorageComponent not found", LogLevel.NORMAL);
			return;
		}
		
		BaseInventoryStorageComponent weaponStorage = userStorageComponent.GetWeaponStorage();
		if(weaponStorage) {
			IEntity weapon = weaponStorage.Get(0);
			if(weapon) {
				MuzzleComponent muzzleComponent = MuzzleComponent.Cast(weapon.FindComponent(MuzzleComponent));
				if(muzzleComponent && muzzleComponent.GetMagazineWell()) {
					magazinePredicate = new CPG_MagazinePredicate(muzzleComponent.GetMagazineWell().Type());
					super.PerformAction(pOwnerEntity, pUserEntity);
				}
			}
		}
	}
	
	override bool CanBeShownScript(IEntity user)
	{	
		SCR_CharacterInventoryStorageComponent userStorageComponent = SCR_CharacterInventoryStorageComponent.Cast(user.FindComponent(SCR_CharacterInventoryStorageComponent));
		if(!userStorageComponent) {
			Print("SCR_CharacterInventoryStorageComponent not found", LogLevel.NORMAL);
			return false;
		}
		
		BaseInventoryStorageComponent weaponStorage = userStorageComponent.GetWeaponStorage();
		if(weaponStorage) {
			IEntity weapon = weaponStorage.Get(0);
			if(weapon) {
				MuzzleComponent muzzleComponent = MuzzleComponent.Cast(weapon.FindComponent(MuzzleComponent));
				if(muzzleComponent && muzzleComponent.GetMagazineWell()) {
					magazinePredicate = new CPG_MagazinePredicate(muzzleComponent.GetMagazineWell().Type());
					return super.CanBeShownScript(user);
				}
			}
		}
		return false;
	}
	
	override string GetItemName() {
		return "Magazine";
	}
}

class CPG_MagazinePredicate : SCR_MagazinePredicate {
	void CPG_MagazinePredicate (typename magazineWell)
	{
		magWellType = magazineWell;
	}
}