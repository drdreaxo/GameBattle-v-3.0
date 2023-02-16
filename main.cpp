#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Character {
  string name;
  int health;
  int currentHealth;
  string spellName;
  int totalPotionsLeft = 3;
};

int minAttackDamage, maxAttackDamage;
int minSpellDamage, maxSpellDamage;
int minPotion, maxPotion;

// Function declarations
void printCharacterInfo(Character hero, Character monster);

void attack(Character &attacker, Character &defender);
void useSpell(Character &caster, Character &target);
void usePotion(Character &character);



  
  void attack(Character & attacker, Character & defender) {
    int damage =
        rand() % (maxAttackDamage - minAttackDamage + 1) + minAttackDamage;
    defender.currentHealth -= damage;
    cout << attacker.name << " attacks for " << damage << " damage." << endl;
    outFile << attacker.name << " attacks for " << damage << " damage." << endl;
  }

  void useSpell(Character & caster, Character & target) {
    int damage = rand() % (maxSpellDamage - minSpellDamage + 1) + minSpellDamage;
    target.currentHealth -= damage;
    cout << caster << " uses " << caster.spellName << " for " << damage
         << " damage." << endl;
    outFile << caster << " uses " << caster.spellName << " for " << damage
            << " damage." << endl;
  }
}


void usePotion(Character &character) {
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

int main() {
  // Open the character info file
  ifstream inFile("AndreaHero.txt");

  if (!inFile) {
    cerr << "Unable to open file CharacterInfo.txt" << endl;
    return 1;
  }

  // Read in the character info
  Character hero, monster;
  inFile >> hero.name >> hero.health >> hero.spellName;
  inFile >> monster.name >> monster.health >> monster.spellName;

  cout << hero.name;

  // Read game parameters
  inFile >> minAttackDamage >> maxAttackDamage >> minSpellDamage >>
      maxSpellDamage >> minPotion >> maxPotion;


  inFile.close();
    
  // open battle resutls file for output
  ofstream outFile("battleResults.txt");

  // Seed the random number generator
  srand(time(0));

  // Game loop
  bool gameOver = false;
  Character *currentCharacter = &hero;
  Character *otherCharacter = &monster;

  while (!gameOver) {
    // Print the current character's turn and health
    cout << "It's " << currentCharacter->name
         << "'s turn. Current HP = " << currentCharacter->health << endl;

    // Print the menu
    cout << "1: Attack\n2: Use " << currentCharacter->spellName
         << "\n3: Use a Potion\nEnter action: ";

    // Get the user's choice
    int choice;
    cin >> choice;

    // Take the appropriate action based on the user's choice
    switch (choice) {
    case 1:
      attack(*currentCharacter, *otherCharacter);
      break;
    case 2:
      useSpell(*currentCharacter, *otherCharacter);
      break;
    case 3:
      usePotion(*currentCharacter);
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
      continue;
    }

    // Check if the game is over
    if (otherCharacter->health <= 0) {
      cout << otherCharacter->name << " has been defeated!" << endl;
      gameOver = true;
    } else {
      // Switch to the other character's turn
      Character *temp = currentCharacter;
      currentCharacter = otherCharacter;
      otherCharacter = temp;
    }
  }

  // game loop ends here...


  // defining functions begings..


  // defining functions begings..

outFile << hero.name << " (" << hero.health << " HP) vs " << monster.name
        << " (" << monster.health << " HP)" << endl;

outFile << hero.name << " final HP: " << hero.currentHealth << endl;
outFile << monster.name << " final HP: " << monster.currentHealth << endl;


outFile.close();
}
