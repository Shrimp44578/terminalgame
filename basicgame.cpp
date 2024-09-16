#include <iostream>
#include <string>
using namespace std;

int turn_damage(void);


class enemy {
public:
    int health;
    int damage;
    int experience_given;
    int level;

    int boss_damage_deal() {
        srand((unsigned)time(NULL) ^ 2); // Seed Gen
        int boss_damage;
        int boss_damage_amt = 1 + (rand() % 90); // Boss Num Gen

        if (boss_damage_amt <= 30)  // Player Damage Decider
        {
            boss_damage = 8;
        }
        else if (boss_damage_amt <= 60)
        {
            boss_damage = 10;
        }
        else if (boss_damage_amt < 90)
        {
            boss_damage = 12;
        }
        else if (boss_damage_amt == 90)
        {
            boss_damage = 30;
        }
        return boss_damage;
    }
};

class player {
public:
    int health;
    int damage;
    int experience;
    int level;
    int damage_mod;
    int health_mod;

    player() {
        damage = 10;
        experience = 0;
        health_mod = 0;
        health = 100 + (2 * health_mod);
        level = 1;
        damage_mod = 0;
        hat.armormod = 0;
        shirt.armormod = 0;
        pants.armormod = 0;
        boots.armormod = 0;
    }
    struct Slot {
    string name;
    float armormod;
    };

    Slot hat;
    Slot shirt;
    Slot pants;
    Slot boots;

    int deal_damage() {
        int dealt_damage, rand_damage;
        rand_damage = turn_damage();
        dealt_damage = rand_damage + damage_mod;

        return dealt_damage;
    }
    
    int turn_damage() {
        srand((unsigned)time(NULL));  // Seed Gen
        int player_damage{};
        int player_damage_amt = 1 + (rand() % 90) ^ 2;  // Player Num Gen

        if (player_damage_amt <= 30)  // Player Damage Decider
        {
            player_damage = 10 - 2;
        }
        else if (player_damage_amt <= 60)
        {
            player_damage = 10;
        }
        else if (player_damage_amt < 90)
        {
            player_damage = 2 + 10;
        }
        else if (player_damage_amt == 90)
        {
            player_damage = 3 * 10;
        }

        return player_damage;

    };

    void take_damage(int boss_damage) {
        int totalarmormod = (1 - (hat.armormod + shirt.armormod + pants.armormod + boots.armormod));
        boss_damage *= totalarmormod;
        health -= boss_damage;
    };

    void enemy_dead(int experience_given) {
        int experience_till_nxt_lvl = level * level;
        string mod_select;
        experience += experience_given;
        cout << "You have " << experience << "\\" << experience_till_nxt_lvl << " exp" << endl;
        while (experience >= experience_till_nxt_lvl) {
                int experience_till_nxt_lvl = level * level;
                if (experience >= experience_till_nxt_lvl) {
                    cout << "Enter\n";
                    cout << "b for more damage\n";
                    cout << "or n for more health\n";
                    getline(cin, mod_select);
                    cin.clear();
                    if (mod_select == "b") {
                        cout << "\n\nYou have leveled up!\n";
                        damage_mod++;
                        experience -= experience_till_nxt_lvl;
                        level++;
                        cout << "You have " << experience << "\\" << experience_till_nxt_lvl << " exp" << endl;
                    }
                    else if (mod_select == "n") {
                        cout << "\n\nYou have leveled up!\n";
                        health_mod++;
                        experience -= experience_till_nxt_lvl;
                        level++;
                        cout << "You have " << experience << "\\" << experience_till_nxt_lvl << " exp" << endl;
                    }
                    else {
                        printf("Enter a valid command\n");
                    }
                }
                else {
                    break;
                }
            }
        }
    };

int main() {
    player p1;

    enemy boss;
        boss.damage = 10;
        boss.experience_given = 10;
        boss.health = 100;
        boss.level = 0;


    string ability;
    for (size_t i = 0; i < 100; i++) {
        int boss_damage = boss.boss_damage_deal();
        cout << "|--------- " << boss.health << " ---------|" << "\n\n\n\n";
        cout << "|--------- " << p1.health << " ---------|" << "\n\n";

        getline(cin, ability);
        cin.clear();
        if (ability == "q") {               // Ability
            int player_damage = p1.deal_damage();
            boss.health -= player_damage;
            p1.take_damage(boss_damage);
            cout << "\n";
        }

        if (ability == "exp") {
            cout << "\n\n" << p1.experience << "\n\n\n";
        }

        if (ability == "kill") {
            boss.health -= 100;
        }

        if (boss.health <= 0) {
            p1.enemy_dead(boss.experience_given);
            p1.health = 100 + (p1.health_mod*2);
            boss.health = 100;
        }
    }
}
