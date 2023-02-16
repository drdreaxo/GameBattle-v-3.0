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
void printCharacterInfo(Character hero, Character monster, ofstream &outFile);
void attack(Character &attacker, Character &defender, ofstream &outFile);
void useSpell(Character &caster, Character &target, ofstream &outFile);
void usePotion(Character &character, ofstream &outFile);

void attack(Character &attacker, Character &defender, ofstream &outFile) {
  int damage =
      rand() % (maxAttackDamage - minAttackDamage + 1) + minAttackDamage;
  defender.currentHealth -= damage;
  cout << attacker.name << " attacks for " << damage << " damage. 🪓" << endl;
  outFile << attacker.name << " attacks for " << damage << " damage.🪓"<< endl;
}

void useSpell(Character &caster, Character &target, ofstream &outFile) {
  int damage = rand() % (maxSpellDamage - minSpellDamage + 1) + minSpellDamage;
  target.currentHealth -= damage;
  cout << caster.name << " uses " << caster.spellName << " for " << damage
       << " damage. 🥊" << endl;
  outFile << caster.name << " uses " << caster.spellName << " for " << damage
          << " damage. 🥊" << endl;
}

void usePotion(Character &character, ofstream &outFile) {
  if (character.totalPotionsLeft <= 3 && character.totalPotionsLeft > 0) {
    if (character.totalPotionsLeft == 2) {
      cout << "WARNING: You have 1 more potion left!!!\n";
      outFile << "WARNING: You have 1 more potion leftt!!!\n";
    }
    if (character.totalPotionsLeft == 1) {
      cout << "You have no potions left!!!\n";
      outFile << "You have no potions left!!!\n";
    }
    int potionAmount = rand() % (maxPotion - minPotion + 1) + minPotion;
    character.currentHealth += potionAmount;
    if (character.currentHealth > character.health) {
      potionAmount = character.currentHealth - character.health;
      character.currentHealth = character.health;
    }

    cout << character.name << " used a potion and gained " << potionAmount
         << " health points. 🔋" << endl;

    outFile << character.name << " used a potion and gained " << potionAmount
            << " health points. 🔋" << endl;
    character.currentHealth = character.currentHealth;
    character.totalPotionsLeft--;
  } else {
    cout << character.name << " is out of potions and loses a turn. 🚨" << endl;
    outFile << character.name << " is out of potions and loses a turn.🚨" << endl;
  }
}

void printCharacterInfo(Character hero, Character monster, ofstream &outFile) {
  outFile << hero.name << " (" << hero.health << " HP) vs " << monster.name
          << " (" << monster.health << " HP)" << endl;
}

// Open the character info

int main() {
  // Open the character info file
  ifstream inFile("AndreaHero.txt");

  if (!inFile) {
    cerr << "Unable to open file AndreaHero.txt" << endl;
    return 1;
  }

  // Read in the character info
  Character hero, monster;
  inFile >> hero.name >> hero.health >> hero.spellName;
  hero.currentHealth = hero.health;

  inFile >> monster.name >> monster.health >> monster.spellName;
  monster.currentHealth = monster.health;

  // Read game parameters
  inFile >> minAttackDamage >> maxAttackDamage >> minSpellDamage >>
      maxSpellDamage >> minPotion >> maxPotion;

  inFile.close();

  // open battle resutls file for output
  ofstream outFile("battleResults.txt");
  if (!outFile) {
    cerr << "Unable to open file battleResults.txt" << endl;
    return 1;
  }

  // Seed the random number generator
  srand(time(0));

  // Game loop
  bool gameOver = false;
  Character *currentCharacter = &hero;
  Character *otherCharacter = &monster;

  cout << "GAME STARTS!";
  outFile << "GAME STARTS!";
  while (!gameOver) {

    // Print the current character's turn and health
    cout << "\n It's " << currentCharacter->name
         << "'s turn. Current HP 🔋 = " << currentCharacter->currentHealth << endl;
    outFile << "\n It's " << currentCharacter->name
         << "'s turn. Current HP 🔋 = " << currentCharacter->currentHealth << endl;
    

    // Print the menu
    cout << "1: Attack\n2: Use " << currentCharacter->spellName
         << "\n3: Use a Potion\nEnter action 🎯: ";
    outFile << "1: Attack\n2: Use " << currentCharacter->spellName
         << "\n3: Use a Potion\nEnter action 🎯: ";

    // Get the user's choice
    int choice;
    cin >> choice;

    // Take the appropriate action based on the user's choice
    switch (choice) {
    case 1:
      attack(*currentCharacter, *otherCharacter, outFile); //
      break;
    case 2:
      useSpell(*currentCharacter, *otherCharacter, outFile);
      break;
    case 3:
      usePotion(*currentCharacter, outFile);
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
      continue;
    }

    // Check if the game is over
    if (otherCharacter->currentHealth <= 0) {
      cout << "\n⚠️ ❗️❗️❗️❗️❗️❗️❗️❗️❗️❗️ GAME OVER ❗️❗️❗️❗️❗️❗️❗️❗️❗️❗️⚠️" << endl;
      outFile << "\n⚠️ ❗️❗️❗️❗️❗️❗️❗️❗️❗️❗️ GAME OVER ❗️❗️❗️❗️❗️❗️❗️❗️❗️❗️⚠️" << endl;

      cout << endl  << otherCharacter->name  << " YOU'RE A LOSER!!!!!!!!!!!!😆 😆 🫣 🤗 🫡 🫢 \n";
      outFile << endl << otherCharacter->name << " YOU'RE A LOSER!!!!!!!!!!!!😆 😆 🫣 🤗 🫡 \n";

      cout << currentCharacter->name << " WINS. 🏆🥇🤩 🥳 🪅";
      outFile << currentCharacter->name << " WINS. 🏆🥇🤩 🥳 🪅";
      gameOver = true;
      } else {
      // Switch to the other character's turn
      Character *temp = currentCharacter;
      currentCharacter = otherCharacter;
      otherCharacter = temp;
    }
  }

  // game loop ends here...

  outFile <<endl <<  hero.name << " (" << hero.health << " HP) vs " << monster.name << " (" 
    << monster.health << " HP)" << endl;
  cout << endl << hero.name << " (" << hero.health << " HP) vs " << monster.name << "("
    << monster.health << " HP)" << endl;

  outFile << endl << hero.name << " final HP: " << hero.currentHealth << endl;
  cout << endl <<hero.name << " final HP: " << hero.currentHealth << endl;

   
  outFile << monster.name << " final HP: " << monster.currentHealth << endl;
  cout << monster.name << " final HP: " << monster.currentHealth << endl;

  

  outFile.close();
}
