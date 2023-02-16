
void attack(Character &attacker, Character &defender, ofstream &outFile) {
  int damage =
      rand() % (maxAttackDamage - minAttackDamage + 1) + minAttackDamage;
  defender.currentHealth -= damage;
  cout << attacker.name << " attacks for " << damage << " damage." << endl;
  outFile << attacker.name << " attacks for " << damage << " damage." << endl;
}

void useSpell(Character &caster, Character &target, ofstream &outFile) {
  int damage = rand() % (maxSpellDamage - minSpellDamage + 1) + minSpellDamage;
  target.currentHealth -= damage;
  cout << caster.name << " uses " << caster.spellName << " for " << damage
       << " damage." << endl;
  outFile << caster.name << " uses " << caster.spellName << " for " << damage
          << " damage." << endl;
}

void usePotion(Character &character, ofstream &outFile) {
  if (character.totalPotionsLeft <= 3 && character.totalPotionsLeft > 0) {
    int potionAmount = rand() % (maxPotion - minPotion + 1) + minPotion;
    character.currentHealth += potionAmount;
    if (character.currentHealth > character.health) {
      potionAmount = character.currentHealth - character.health;
      character.currentHealth = character.health;
    }

    cout << character.name << " used a potion and gained " << potionAmount
         << " health points." << endl;

    outFile << character.name << " used a potion and gained " << potionAmount
            << " health points." << endl;
    character.currentHealth = character.currentHealth;
    character.totalPotionsLeft--;
  } else {
    cout << character.name << " is out of potions and loses a turn." << endl;
    outFile << character.name << " is out of potions and loses a turn." << endl;
  }
}

void printCharacterInfo(Character hero, Character monster, ofstream &outFile) {
  outFile << hero.name << " (" << hero.health << " HP) vs " << monster.name
          << " (" << monster.health << " HP)" << endl;
}