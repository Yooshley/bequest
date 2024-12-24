// Copyright Yooshley. All rights reserved.


#include "BequestGameplayTags.h"

namespace BequestGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Move, "Player.Ability.Move");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip, "Player.Ability.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Charge, "Player.Ability.Charge");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack, "Player.Ability.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Deflect, "Player.Ability.Deflect");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Guard, "Player.Ability.Guard");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Evade, "Player.Ability.Evade");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Guard_Left, "Player.Status.Guard.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Guard_Right, "Player.Status.Guard.Right");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip, "Player.Event.Equip");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Equipment_Sword_2H, "Player.Equipment.Sword.2H");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Hurt, "Shared.Ability.Hurt");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hit, "Shared.Event.Hit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Hurt, "Shared.Event.Hurt");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Hurt_Front, "Shared.Status.Hurt.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Hurt_Back, "Shared.Status.Hurt.Back");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Hurt_Left, "Shared.Status.Hurt.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Hurt_Right, "Shared.Status.Hurt.Right");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_Damage, "Shared.SetByCaller.Damage");
}