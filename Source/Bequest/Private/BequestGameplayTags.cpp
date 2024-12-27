// Copyright Yooshley. All rights reserved.


#include "BequestGameplayTags.h"

namespace BequestGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Move, "Character.Ability.Move");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Equip, "Character.Ability.Equip");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Charge, "Character.Ability.Charge");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Attack, "Character.Ability.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Deflect, "Character.Ability.Deflect");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Guard, "Character.Ability.Guard");
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Evade, "Character.Ability.Evade");
	
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Block, "Character.Ability.Block"); //Guard
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Stun, "Character.Ability.Stun"); //Guard
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Absorb, "Character.Ability.Absorb"); //Armor
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Break, "Character.Ability.Break"); //Armor
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Hurt, "Character.Ability.Hurt"); //Life
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Die, "Character.Ability.Die"); //Life
	UE_DEFINE_GAMEPLAY_TAG(Character_Ability_Respawn, "Character.Ability.Respawn");
	
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Guarded, "Character.State.Guarded");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Guarded_Left, "Character.State.Guarded.Left");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Guarded_Right, "Character.State.Guarded.Right");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Armored, "Character.State.Armored");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Suppressed, "Character.State.Suppressed"); //Blocks Guard Regen
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Dead, "Character.State.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Character_State_Invulnerable, "Character.State.Invulnerable"); //Blocks All Damage
	
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Equip, "Character.Event.Equip");
	
	UE_DEFINE_GAMEPLAY_TAG(Character_Equipment_Sword_2H, "Character.Equipment.Sword.2H");
	
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Attack, "Character.Event.Attack");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Attack_Light, "Character.Event.Attack.Light");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Attack_Heavy, "Character.Event.Attack.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Hit, "Character.Event.Hit");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Respawn, "Character.Event.Respawn");
	
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Stun, "Character.Event.Stun");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Block, "Character.Event.Block");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Absorb, "Character.Event.Absorb");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Break, "Character.Event.Break");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Hurt_Front, "Character.Event.Hurt.Front");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Hurt_Back, "Character.Event.Hurt.Back");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Hurt_Left, "Character.Event.Hurt.Left");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Hurt_Right, "Character.Event.Hurt.Right");
	UE_DEFINE_GAMEPLAY_TAG(Character_Event_Death, "Character.Event.Death");
	
	UE_DEFINE_GAMEPLAY_TAG(Character_SetByCaller_Damage_Life, "Character.SetByCaller.Damage.Life");
	UE_DEFINE_GAMEPLAY_TAG(Character_SetByCaller_Damage_Armor, "Character.SetByCaller.Damage.Armor");
	UE_DEFINE_GAMEPLAY_TAG(Character_SetByCaller_Damage_Guard, "Character.SetByCaller.Damage.Guard");
}