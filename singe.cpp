#include <iostream>
#include <cassert>
#include <cstring>
#include <fstream> // pour ifstream
#include <iomanip> // pour setw

using namespace std;
enum { MAX_CHAR = 26 };
#define FINISH1 '?'
#define FINISH2 '!'
#define HUMAIN 'H'
#define ROBOT 'R'

#define VRAI 1
# define FAUX 0
typedef int BOOL;

struct Partie
{
  char mot[MAX_CHAR];
  unsigned int taillemot;
  unsigned int nbJoueurs;
  unsigned int dernierJoueurPerdant;
  BOOL nouveauTour;
  char motJoueurDeviner[MAX_CHAR];
};

void mancheJeu(char pl[], Partie& partie);
void affichageTexte(Partie& partie);
void LettreAleatoireRobot(Partie& partie);
void ajoutLettre(Partie& partie, char LettreRobot);
void abandonJoueur(Partie& partie, unsigned int indice, const char* ordre, float* score);
int ajoutLettre(Partie& partie, const char* ordre, unsigned int indice);
void saisirMotHumain(Partie& partie, const char* ordre, unsigned int indice, float* score);
void afficheMotExiste(Partie& partie, const char* ordre, float* score, unsigned int indice, char trouve_mot[]);
unsigned int trouve_Dico(Partie& partie, char trouve_mot[]);
void debutMotFaux(Partie& partie, const char* ordre, float* score, unsigned int indice, char mot[]);
int verifMot(Partie& partie, char mot[], unsigned int indice, const char* ordre, float* score);
void afficheScore(Partie& partie, const char* ordre, float* score);
void finduJeu(Partie& partie, float* score);
void nouvelleManche(Partie& partie, const char* ordre, float* score);
void init(Partie& partie);
void AffichemotExistePas(Partie& partie, const char* ordre, float* score, unsigned int indice, char mot[]);
void resetMotJoueur(Partie& partie);



int main(int argc, char* argv[])
{
  Partie p;
  init(p);
  mancheJeu(argv[1], p);
}


void resetMotJoueur(Partie& partie) {
  for (unsigned int i = 0; i < MAX_CHAR; ++i)
    partie.motJoueurDeviner[i] = NULL;
}
/**
 * @brief Initialiser les structure.
 * @param
 */
void init(Partie& partie)
{

  for (unsigned int i = 0; i < MAX_CHAR; i++) {
    partie.mot[i] = NULL;
    partie.motJoueurDeviner[i] = NULL;
  }
  partie.taillemot = 0;
  partie.nbJoueurs = 0;
  partie.dernierJoueurPerdant = -1;
  partie.nouveauTour = FAUX;
}

/**
 * @brief initialiser lors d'une nouvelle manche.
 *
 * \param joueur
 */
void nouvelleManche(Partie& partie, const char* ordre, float* score) {
  for (unsigned int i = 0; i < MAX_CHAR; i++) {
    partie.mot[i] = NULL;
    partie.taillemot = 0;

  }

  if (partie.dernierJoueurPerdant + 1 > 1) {

    for (unsigned int i = partie.dernierJoueurPerdant; i < partie.nbJoueurs; ++i)
    {
      if (partie.nouveauTour == VRAI) {
        i = 0;
        partie.nouveauTour = FAUX;
      }
      cout << i + 1 << ordre[i] << ", (";
      affichageTexte(partie);
      cout << ") > ";
      int letter = ajoutLettre(partie, ordre, i);
      switch (letter) {
      case 0:
        if (trouve_Dico(partie, partie.mot)) {
          afficheMotExiste(partie, ordre, score, i, partie.mot);
          nouvelleManche(partie, ordre, score);
        }
        break;
      case 1:
        // si le joueur a entré '?'
        // saisirMotHumain renvoie la chaine de caractères écrit par le joueur
        saisirMotHumain(partie, ordre, i, score);
        if (verifMot(partie, partie.motJoueurDeviner, i, ordre, score)) {
          debutMotFaux(partie, ordre, score, i, partie.motJoueurDeviner);
          nouvelleManche(partie, ordre, score);
        }
        else
          if (trouve_Dico(partie, partie.motJoueurDeviner)) {
            if (i == 0)
              afficheMotExiste(partie, ordre, score, partie.nbJoueurs - 1, partie.motJoueurDeviner);
            else
              afficheMotExiste(partie, ordre, score, i, partie.motJoueurDeviner);
            nouvelleManche(partie, ordre, score);
          }
        break;
      case 2:
        //si le joueur a entré '!'
        abandonJoueur(partie, i, ordre, score);
        nouvelleManche(partie, ordre, score);
        break;

      }
    }

    // on met le bool a vrai
  }
  partie.nouveauTour = VRAI;
}

void finduJeu(Partie& partie, float* score) {

  for (unsigned int i = 0; i < partie.nbJoueurs; ++i) {
    if (score[i] == 1) {
      cout << "La partie est finie" << endl;
      exit(0);
    }
  }
}

/**
 * @brief Afficher le score des quarts de singe.
 *
 * \param joueur
 * \param indice
 * \param ordre
 * \param score
 */
void afficheScore(Partie& partie, const char* ordre, float* score) {

  for (unsigned int i = 0; i < partie.nbJoueurs - 1; ++i) {
    cout << i + 1 << ordre[i] << " : " << score[i] << "; ";
  }

  cout << partie.nbJoueurs << ordre[partie.nbJoueurs - 1] << " : " << score[partie.nbJoueurs - 1] << endl;
  finduJeu(partie, score);
}

/**
 * @brief cherchez si deux mots commencent par les mêmes lettres.
 *
 * \param joueur
 * \param ordre
 */
int verifMot(Partie& partie, char mot[], unsigned int indice, const char* ordre, float* score) {
  for (unsigned int i = 0; i < strlen(partie.mot); ++i) {
    if (partie.mot[i] != mot[i]) {
      /**/
      return 1;
    }
  }
  return 0;
}


/**
 * @brief afficher le mot ne commence pas par les lettres attendues
 *
 * \param partie
 * \param ordre
 * \param score
 * \param indice
 * \param mot
 */
void debutMotFaux(Partie& partie, const char* ordre, float* score, unsigned int indice, char mot[]) {
  cout << "le mot " << mot << " ne commence pas par les lettres attendues, le joueur " << indice << ordre[indice - 1] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice - 1;
  score[indice - 1] += 0.25;
  afficheScore(partie, ordre, score);
}

/**
 * @brief verifie si le mot entré par le joueur existe
 * @param joueur
 * @param trouve_mot
 */
unsigned int trouve_Dico(Partie& partie, char trouve_mot[])
{
  for (int i = 0; i < strlen(trouve_mot); ++i)
    trouve_mot[i] = toupper(trouve_mot[i]);

  // lecture du dictionnaire mot à mot
  ifstream in("ods4.txt"); // on ouvre le fichier

  char Dico[MAX_CHAR];

  in >> setw(MAX_CHAR) >> Dico;

  while (in)
  {
    if (strcmp(trouve_mot, Dico) == 0 && strlen(Dico) > 2) {
      return 1; // return 1 si le mot existe
    }
    in >> setw(MAX_CHAR) >> Dico;
  }
  in.close(); // on ferme le fichier
  return 0;   // return 0 si le mot existe pas
}

void afficheMotExiste(Partie& partie, const char* ordre, float* score, unsigned int indice, char trouve_mot[]) {
  // compare le mot saisi par l'utilisateur et le dico
  cout << "le mot " << trouve_mot << " existe, ";
  if (indice == partie.nbJoueurs)
  {
    indice -= (partie.nbJoueurs);
  }

  cout << indice + 1 << ordre[indice] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice;
  score[indice] += 0.25;
  afficheScore(partie, ordre, score);
  finduJeu(partie, score);
}


void AffichemotExistePas(Partie& partie, const char* ordre, float* score, unsigned int indice, char mot[]) {
  if (indice + 1 == 1) {
    indice = partie.nbJoueurs;
  }
  cout << "le mot " << mot << " n'existe pas, " << indice << ordre[indice - 1] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice - 1;
  score[indice - 1] += 0.25;
  afficheScore(partie, ordre, score);
  finduJeu(partie, score);
}


/**
 * @brief vérifier si le mot formé existe.
 * @param rank
 * @param ordre
 * @param indice
 */
void saisirMotHumain(Partie& partie, const char* ordre, unsigned int indice, float* score)
{
  char trouve_mot[MAX_CHAR];
  // le premier joueur doit demander au dernier joueur
  if (indice == 0)
  {
    while (ordre[indice] == HUMAIN || ordre[indice] == ROBOT)
    {
      indice++;
    }
  }
  cout << indice << ordre[indice - 1];

  cout << ", saisir le mot > ";
  cin >> trouve_mot;
  for (unsigned int i = 0; i < strlen(trouve_mot); ++i) {
    trouve_mot[i] = toupper(trouve_mot[i]);
  }
  resetMotJoueur(partie);
  for (int i = 0; i < strlen(trouve_mot); ++i) {
    partie.motJoueurDeviner[i] = trouve_mot[i];
  }
}
/**
 * @brief Ajoute une lettre au mot recherché.
 * @param joueur
 * @param ordre
 * @param indice
 *
 */
int ajoutLettre(Partie& partie, const char* ordre, unsigned int indice)
{
  //if (partie.taillemot == 0 && ordre[indice] == ROBOT) {
  //  LettreAleatoireRobot(partie);
  //  return;
  //}
  char mot;
  unsigned int i = 0;
  cin >> mot;

  if (mot == FINISH1)
    return 1;


  if (mot == FINISH2)
    return 2;

  while (partie.mot[i] != NULL)
  {
    i++;
  }
  if (partie.mot[i] == NULL)
  {
    partie.mot[i] = toupper(mot);
    partie.taillemot++;
  }
  return 0;
}

void abandonJoueur(Partie& partie, unsigned int indice, const char* ordre, float* score) {
  if (indice == partie.nbJoueurs)
    indice -= (partie.nbJoueurs - 1);
  cout << "Le joueur " << indice + 1 << ordre[indice] << " abandonne la manche et prend un quart de singe" << endl; // si l'utilisateur rentre '!'
  partie.dernierJoueurPerdant = indice;
  score[indice] += 0.25;
  afficheScore(partie, ordre, score);
  finduJeu(partie, score);
}

/** @brief ajout d'une lettre au mot recherche par les robots
*   @param joueur
*   @param LettreRobot
*/
void ajoutLettre(Partie& partie, char LettreRobot)
{
  unsigned int i = 0;
  while (partie.mot[i] != NULL)
  {
    i++;
  }
  partie.mot[i] = LettreRobot;
}

/**
 * @brief Générer une lettre aléatoire si le robot joue en premier
 *
 * @param joueur
 */
void LettreAleatoireRobot(Partie& partie)
{
  srand(time(NULL));
  char LettreAleatoire = 'A' + rand() % 26;
  cout << LettreAleatoire << endl;
  ajoutLettre(partie, LettreAleatoire);
}

/**
 * @brief Afficher le mot formé.
 * @param joueur
 */
void affichageTexte(Partie& partie)
{
  unsigned int i = 0;
  while (partie.mot[i] != NULL)
  {
    cout << partie.mot[i];
    i++;
  }
}

/**
 * @brief Determine le type de joueurs.
 * @param pl[]
 * @param joueur
 */
void mancheJeu(char pl[], Partie& partie)
{
  char* ordre;
  float* score;

  partie.nbJoueurs = unsigned int(strlen(pl));
  assert(partie.nbJoueurs >= 2);
  ordre = new char[partie.nbJoueurs];
  score = new float[partie.nbJoueurs];

  for (unsigned int i = 0; i < partie.nbJoueurs; ++i) {
    score[i] = 0.;
    ordre[i] = NULL;
  }
  for (unsigned int i = 0; i < partie.nbJoueurs; ++i) {
    ordre[i] = toupper(pl[i]);
    assert(ordre[i] == HUMAIN || ordre[i] == ROBOT);
  }



  while (partie.taillemot < MAX_CHAR)
  {
    for (unsigned int i = 0; i < partie.nbJoueurs; ++i)
    {
      if (partie.nouveauTour == VRAI) {
        i = 0;
        partie.nouveauTour = FAUX;
      }

      cout << i + 1 << ordre[i] << ", (";
      affichageTexte(partie);
      cout << ") > ";
      int letter = ajoutLettre(partie, ordre, i);
      switch (letter) {

      case 0:
        if (trouve_Dico(partie, partie.mot)) {
          afficheMotExiste(partie, ordre, score, i, partie.mot);
          nouvelleManche(partie, ordre, score);
        }
        break;

      case 1:
        // si le joueur a entré '?'
        // saisirMotHumain renvoie la chaine de caractères écrit par le joueur
        saisirMotHumain(partie, ordre, i, score);
        // reaffecte partie.motJoueurDeviner
        if (verifMot(partie, partie.motJoueurDeviner, i, ordre, score)) {
          debutMotFaux(partie, ordre, score, i, partie.motJoueurDeviner);
          nouvelleManche(partie, ordre, score);
        }
        else if (trouve_Dico(partie, partie.motJoueurDeviner)) {
          if (i == 0)
            afficheMotExiste(partie, ordre, score, partie.nbJoueurs - 1, partie.motJoueurDeviner);
          else
            afficheMotExiste(partie, ordre, score, i, partie.motJoueurDeviner);

          nouvelleManche(partie, ordre, score);
        }
        else {
          AffichemotExistePas(partie, ordre, score, i, partie.motJoueurDeviner);
          nouvelleManche(partie, ordre, score);
        }
        break;

      case 2:
        //si le joueur a entré '!'
        abandonJoueur(partie, i, ordre, score);
        nouvelleManche(partie, ordre, score);
        break;

      }
    }
  }
}