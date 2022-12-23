#include <iostream>
#include <cstring>
#include <fstream> // pour ifstream
#include <iomanip> // pour setw

#pragma warning(disable: 4996)

using namespace std;

enum { MAX_CHAR = 26, MAX_ENTREE = 1 };
#define FINISH1 '?'
#define FINISH2 '!'
#define HUMAIN 'H'
#define ROBOT 'R'
#define CHAINE_VIDE '\0'
#define VRAI 1
#define FAUX 0
typedef int BOOL;

#define TRACE 0

struct Partie {
  char mot[MAX_CHAR];
  unsigned int taillemot;
  unsigned int nbJoueurs;
  unsigned int dernierJoueurPerdant;
  BOOL nouveauTour;
  char motJoueurDeviner[MAX_CHAR];
  char* ordre;
  float* score;
  char motRobot[1];
};

int tailleDico = 0;
char** pDico = NULL;

void mancheJeu(Partie& partie);
void affichageTexte(const Partie& partie);
void LettreAleatoireRobot(Partie& partie);
void abandonJoueur(Partie& partie, unsigned int indice);
int ajoutLettre(Partie& partie, unsigned int indice);
void saisirMotHumain(Partie& partie, unsigned int indice);
void afficheMotExiste(Partie& partie, unsigned int indice, char trouve_mot[]);
unsigned int trouve_Dico(Partie& partie, char trouve_mot[]);
void debutMotFaux(Partie& partie, unsigned int indice, char mot[]);
int verifMot(Partie& partie, char mot[], unsigned int indice);
void afficheScore(Partie& partie);
void finduJeu(Partie& partie);
void nouvelleManche(Partie& partie);
void init(Partie& partie, char pl[]);
void AffichemotExistePas(Partie& partie, unsigned int indice, char mot[]);
int LettreRobot(Partie& partie, unsigned int indice);
void resetMotJoueur(Partie& partie);
void freeDico();
char** buildDico(int& oMaxTaille);



void freeDico() {
  for (int i = 0; i < tailleDico; i++)
    delete[] pDico[i];
  delete[] pDico;
}

char** buildDico(int& oMaxTaille) {
  int TailleFixe = 1000;
  int Max = TailleFixe;
  int index = 0;
  char** pListMots = new char* [Max];

  ifstream in("ods4.txt"); // on ouvre le fichier

  char* pMot = new char[MAX_CHAR];
  in >> setw(MAX_CHAR) >> pMot;

  while (in) {
    if (strlen(pMot) > 2) {
      pListMots[index] = pMot;
      index++;
    }

    if (index == Max) {
      // On a atteind ma taille max, on réalloue un autre tableau avec la taille 2 x Max
      int NewMaw = Max + TailleFixe;
      char** pNewListMots = new char* [NewMaw];

      // On copie les anciens
      for (int i = 0; i < Max; i++) {
        pNewListMots[i] = pListMots[i];
      }
      // On detruit l'ancien
      delete[] pListMots;

      // On réaffecte le nouveau
      pListMots = pNewListMots;

      Max = NewMaw;
    }
    //
    pMot = new char[MAX_CHAR];
    in >> setw(MAX_CHAR) >> pMot;
    if (!in)break;
  }

  oMaxTaille = index;

  in.close(); // on ferme le fichier

  return pListMots;
}



void detruireJeu(Partie& partie) {
  delete[] partie.ordre;
  delete[]partie.score;
}


void resetMotJoueur(Partie& partie) {
  for (unsigned int i = 0; i < MAX_CHAR; ++i)
    partie.motJoueurDeviner[i] = CHAINE_VIDE;
}
/**
 * @brief Initialiser les structure.
 */
void init(Partie& partie, char pl[]) {

  for (unsigned int i = 0; i < MAX_CHAR; i++) {
    partie.mot[i] = CHAINE_VIDE;
    partie.motJoueurDeviner[i] = CHAINE_VIDE;
  }
  partie.taillemot = 0;
  partie.nbJoueurs = 0;
  partie.dernierJoueurPerdant = -1;
  partie.nouveauTour = FAUX;
  partie.nbJoueurs = strlen(pl);
  // pl est la chaine de caractères passée en paramètre de la fonction, et qui correspond à argv[1]
  if (partie.nbJoueurs < 2) {
    cerr << "Pour jouer au quart de singe, il faut etre au moins 2 joueurs." << endl;
    exit(0);
  }
  partie.ordre = new char[partie.nbJoueurs];
  // tableau de char qui stockera le joueur suivant son type ( H ou R )
  partie.score = new float[partie.nbJoueurs];
  // tableau de float qui stockera les quart de singe
  for (unsigned int i = 0; i < partie.nbJoueurs; ++i) {
    partie.score[i] = 0.;
  }
  for (unsigned int i = 0; i < partie.nbJoueurs; ++i) {
    partie.ordre[i] = toupper(pl[i]);
    if (partie.ordre[i] != HUMAIN && partie.ordre[i] != ROBOT) {
      cerr << "Le type de joueurs est incorrect." << endl << "Renseignez 'H' pour un Humain, 'R' pour un Robot." << endl;
      exit(0);
    }
  }
}

/**
 * @brief initialiser lors d'une nouvelle manche.
 */
void nouvelleManche(Partie& partie) {
  for (unsigned int i = 0; i < MAX_CHAR; i++) {
    partie.mot[i] = CHAINE_VIDE;
    partie.taillemot = 0;
  }

  if (partie.dernierJoueurPerdant + 1 > 1) {

    for (unsigned int i = partie.dernierJoueurPerdant; i < partie.nbJoueurs; ++i) {
      if (partie.nouveauTour == VRAI) {
        i = 0;
        partie.nouveauTour = FAUX;
      }
      cout << i + 1 << partie.ordre[i] << ", (";
      affichageTexte(partie);
      cout << ") > ";
      int letter = 0;
      if (partie.ordre[i] == HUMAIN)
        letter = ajoutLettre(partie, i);
      else {
        letter = LettreRobot(partie, i);
      }
      switch (letter) {
      case 0:
        if (trouve_Dico(partie, partie.mot)) {
          afficheMotExiste(partie, i, partie.mot);
          nouvelleManche(partie);
        }
        break;
      case 1:
        // si le joueur a entré '?'
        // saisirMotHumain renvoie la chaine de caractères écrit par le joueur
        saisirMotHumain(partie, i);
        if (verifMot(partie, partie.motJoueurDeviner, i)) {
          debutMotFaux(partie, i, partie.motJoueurDeviner);
          nouvelleManche(partie);
        }
        else
          if (trouve_Dico(partie, partie.motJoueurDeviner)) {
            if (i == 0)
              afficheMotExiste(partie, partie.nbJoueurs - 1, partie.motJoueurDeviner);
            else
              afficheMotExiste(partie, i, partie.motJoueurDeviner);
            nouvelleManche(partie);
          }
        break;
      case 2:
        //si le joueur a entré '!'
        abandonJoueur(partie, i);
        nouvelleManche(partie);
        break;
      }
    }
    // on met le bool a vrai
  }
  partie.nouveauTour = VRAI;
}

void finduJeu(Partie& partie) {

  for (unsigned int i = 0; i < partie.nbJoueurs; ++i) {
    if (partie.score[i] == 1) {
      cout << "La partie est finie" << endl;
      detruireJeu(partie);
      freeDico();
      exit(0);
    }
  }
}

/**
 * @brief Afficher le score des quarts de singe.
 */
void afficheScore(Partie& partie) {
  for (unsigned int i = 0; i < partie.nbJoueurs - 1; ++i) {
    cout << i + 1 << partie.ordre[i] << " : " << partie.score[i] << "; ";
  }
  cout << partie.nbJoueurs << partie.ordre[partie.nbJoueurs - 1] << " : " << partie.score[partie.nbJoueurs - 1] << endl;
  finduJeu(partie);
}

/**
 * @brief cherchez si deux mots commencent par les mêmes lettres.
 */
int verifMot(Partie& partie, char mot[], unsigned int indice) {
  for (unsigned int i = 0; i < strlen(partie.mot); ++i) {
    if (partie.mot[i] != mot[i]) {
      return 1;
    }
  }
  return 0;
}


/**
 * @brief afficher le mot ne commence pas par les lettres attendues
 */
void debutMotFaux(Partie& partie, unsigned int indice, char mot[]) {
  if (indice + 1 == 1) indice = partie.nbJoueurs;
  cout << "le mot " << mot << " ne commence pas par les lettres attendues, le joueur " << indice << partie.ordre[indice - 1] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice - 1;
  partie.score[indice - 1] += 0.25;
  afficheScore(partie);
}

/**
 * @brief verifie si le mot entré par le joueur existe
 */
unsigned int trouve_Dico(Partie& partie, char trouve_mot[])
{
  if(partie.taillemot <= 2)
    return 0;

  for (int i = 0; i < strlen(trouve_mot); ++i)
    trouve_mot[i] = toupper(trouve_mot[i]);

  if (TRACE)
    cout << "trouve_Dico trouve_mot = " << trouve_mot << endl;

  for (int i = 0; i < tailleDico; i++) {
    char* pmot = pDico[i];
    if (TRACE)
      cout << "trouve_Dico pmot = " << pmot << " index = " << i << endl;

    if (strcmp(trouve_mot, pmot) == 0) {
      if (TRACE)
        cout << "trouve_Dico trouve_mot = pmot" << endl;

      return 1;
    }
  }
  return 0;   // return 0 si le mot existe pas
}

void afficheMotExiste(Partie& partie, unsigned int indice, char trouve_mot[]) {
  // compare le mot saisi par l'utilisateur et le dico
  cout << "le mot " << trouve_mot << " existe, ";
  if (indice == partie.nbJoueurs) {
    indice -= (partie.nbJoueurs);
  }
  cout << "le joueur " << indice + 1 << partie.ordre[indice] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice;
  partie.score[indice] += 0.25;
  afficheScore(partie);
  finduJeu(partie);
}

void AffichemotExistePas(Partie& partie, unsigned int indice, char mot[]) {
  if (indice + 1 == 1) {
    indice = partie.nbJoueurs;
  }
  cout << "le mot " << mot << " n'existe pas, " << indice << partie.ordre[indice - 1] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice - 1;
  partie.score[indice - 1] += 0.25;
  afficheScore(partie);
  finduJeu(partie);
}

/**
 * @brief Rendre un mot pour le robot.
 */
void trouve_Dico_Robot(Partie& partie) {
  //ifstream in("ods4.txt"); // on ouvre le fichier
  //char motDico[MAX_CHAR];
  //in >> setw(MAX_CHAR) >> motDico;
  //while (strlen(motDico) <= 2) in >> setw(MAX_CHAR) >> motDico;
  int i = 0;
  for (i; i < tailleDico; ++i) {
    if (strncmp(pDico[i], partie.mot, partie.taillemot) == 0) {
      resetMotJoueur(partie);
      strcpy(partie.motJoueurDeviner, pDico[i]);
      cout << pDico[i] << endl;
      break;
    }
  }
  if (i == tailleDico) {
    resetMotJoueur(partie);
    strcpy(partie.motJoueurDeviner, partie.mot);
    cout << partie.mot << endl;
  }

}


/**
 * @brief vérifier si le mot formé existe.
 */
void saisirMotHumain(Partie& partie, unsigned int indice) {
  char trouve_mot[MAX_CHAR];
  // le premier joueur doit demander au dernier joueur
  if (indice == 0) {
    while (partie.ordre[indice] == HUMAIN || partie.ordre[indice] == ROBOT) {
      indice++;
    }
  }
  cout << indice << partie.ordre[indice - 1];
  cout << ", saisir le mot > ";
  if (partie.ordre[indice - 1] == HUMAIN) {
    cin >> trouve_mot;
    /*assert(strlen(trouve_mot) < 26);*/
    if (strlen(trouve_mot) >= 26) {
      cerr << "Le mot saisi depasse la limite de caracteres." << endl;

      exit(0);
    }
    for (unsigned int i = 0; i < strlen(trouve_mot); ++i) {
      trouve_mot[i] = toupper(trouve_mot[i]);
    }
    resetMotJoueur(partie);
    for (int i = 0; i < strlen(trouve_mot); ++i) {
      partie.motJoueurDeviner[i] = trouve_mot[i];
    }
    return;
  }
  else {
    trouve_Dico_Robot(partie);
    return;
  }
}
/**
 * @brief Ajoute une lettre au mot recherché.
 *
 */
int ajoutLettre(Partie& partie, unsigned int indice) {
  char mot;
  unsigned int i = 0;
  //if (partie.ordre[indice] == ROBOT && partie.taillemot == 0) {
  //  LettreAleatoireRobot(partie);
  //  return 0;
  //}
  cin >> mot;
  cin.ignore(INT_MAX, '\n');
  if(TRACE)
    cout << "ajoutLettre mot: " << mot << endl;

  if (mot == FINISH1) {
    if (TRACE)
      cout << "ajoutLettre mot == FINISH1" << endl;
    return 1;
  }
  if (mot == FINISH2) {
    if (TRACE)
      cout << "ajoutLettre mot == FINISH2" << endl;

    return 2;
  }
  while (partie.mot[i] != CHAINE_VIDE) {
    i++;
  }
  if (TRACE)
    cout << "ajoutLettre i = " << i << endl;

  if (partie.mot[i] == CHAINE_VIDE) {
    partie.mot[i] = toupper(mot);
    partie.taillemot++;
  }
  return 0;
}

void abandonJoueur(Partie& partie, unsigned int indice) {
  if (indice == partie.nbJoueurs)
    indice -= (partie.nbJoueurs - 1);
  cout << "le joueur " << indice + 1 << partie.ordre[indice] << " abandonne la manche et prend un quart de singe" << endl; // si l'utilisateur rentre '!'
  partie.dernierJoueurPerdant = indice;
  partie.score[indice] += 0.25;
  afficheScore(partie);
  finduJeu(partie);
}

/** @brief ajout d'une lettre au mot recherche par les robots
 */
void ajoutLettre(Partie& partie) {
  unsigned int i = 0;
  while (partie.mot[i] != CHAINE_VIDE) {
    i++;
  }
  partie.taillemot++;
  partie.mot[i] = partie.motRobot[0];
  partie.motRobot[0] = CHAINE_VIDE;
}

/**
 * @brief Générer une lettre aléatoire si le robot joue en premier
 */
void LettreAleatoireRobot(Partie& partie) {

  char LettreAleatoire = 'A' + rand() % MAX_CHAR;
  cout << LettreAleatoire << endl;
  partie.motRobot[0] = LettreAleatoire;
  ajoutLettre(partie);
}


unsigned int motDebutExiste(Partie& partie, char mot[]) {

  for (int i = 0; i < tailleDico; i++) {
    char* motDico = pDico[i];
    if (strncmp(mot, motDico, partie.taillemot + 1) == 0) {
      return 1;
    }

  }
  return 0;
}


unsigned int verifDebutMot(Partie& partie, char mot[]) {
  char lettreRand = 'A' + rand() % 26;
  mot[partie.taillemot] = lettreRand;
  partie.motRobot[0] = lettreRand;

  if (TRACE)
    cout << "verifDebutMot lettreRand =" << lettreRand << endl;

  unsigned int motExiste = motDebutExiste(partie, mot);
  if (motExiste) {
    if (TRACE)
      cout << "verifDebutMot motExiste =" << motExiste << endl;

    int motTrouve = trouve_Dico(partie, mot);
    if (motTrouve) {
      if (TRACE)
        cout << "verifDebutMot motTrouve =" << motTrouve << endl;

      verifDebutMot(partie, mot);
    }
    else {
      if (TRACE)
        cout << "verifDebutMot return =" << 1 << endl;

      return 1;
    }
  }
  else {
    verifDebutMot(partie, mot);
  }
}



int trouve_mot_DICO(Partie& partie) {

  char* motDico = new char[partie.taillemot + 1];

  int i = 0;
  while (i < tailleDico) {
    if (strlen(pDico[i]) > partie.taillemot) {
      strncpy(motDico, pDico[i], partie.taillemot);
      if (strncmp(motDico, partie.mot, partie.taillemot) == 0) {
        int motExiste = verifDebutMot(partie, motDico);
        if (motExiste) {
          delete[] motDico;
          return 0;
        }
      }
    }
    i++;
  }
  if (i == tailleDico) {
    delete[]motDico;
    return 1;   // return 1 si le mot existe pas
  }
}

/**
 * @brief Fonction qui renvoie un chiffre en fonction du robot... ( a completer).
 */
int LettreRobot(Partie& partie, unsigned int indice) {
  if (partie.taillemot == 0) {
    LettreAleatoireRobot(partie);
    return 0;
  }
  int num = trouve_mot_DICO(partie);
  if (num == 0) {
    cout << partie.motRobot[0] << endl;
    ajoutLettre(partie);
  }
  else {
    cout << "?" << endl;
  }
  return num;

}

/**
 * @brief Afficher le mot formé.
 */
void affichageTexte(const Partie& partie) {
  unsigned int i = 0;
  while (partie.mot[i] != CHAINE_VIDE) {
    cout << partie.mot[i];
    i++;
  }
}

/**
 * @brief Determine le type de joueurs.
 */
void mancheJeu(Partie& partie) {

  while (partie.taillemot < MAX_CHAR) {
    for (unsigned int i = 0; i < partie.nbJoueurs; ++i) {
      if (partie.nouveauTour == VRAI) {
        i = 0;
        partie.nouveauTour = FAUX;
      }
      cout << i + 1 << partie.ordre[i] << ", (";
      affichageTexte(partie);
      cout << ") > ";

      int letter = 0;
      if (partie.ordre[i] == HUMAIN)
        letter = ajoutLettre(partie, i);
      else {
        letter = LettreRobot(partie, i);
      }
      switch (letter) {
      case 0:

        if (trouve_Dico(partie, partie.mot)) {
          afficheMotExiste(partie, i, partie.mot);
          nouvelleManche(partie);
        }
        break;
      case 1:
        // si le joueur a entré '?'
        // saisirMotHumain renvoie la chaine de caractères écrit par le joueur
        saisirMotHumain(partie, i);
        // reaffecte partie.motJoueurDeviner
        if (verifMot(partie, partie.motJoueurDeviner, i)) {
          debutMotFaux(partie, i, partie.motJoueurDeviner);
          nouvelleManche(partie);
        }
        else if (trouve_Dico(partie, partie.motJoueurDeviner)) {
          if (i == 0)
            afficheMotExiste(partie, partie.nbJoueurs, partie.motJoueurDeviner);
          else
            afficheMotExiste(partie, i, partie.motJoueurDeviner);

          nouvelleManche(partie);
        }
        else {
          AffichemotExistePas(partie, i, partie.motJoueurDeviner);
          nouvelleManche(partie);
        }
        break;
      case 2:
        //si le joueur a entré '!'
        abandonJoueur(partie, i);
        nouvelleManche(partie);
        break;

      }
    }
  }
}
int main(int argc, char* argv[]) {
  srand(time(NULL));
  pDico = buildDico(tailleDico);
  Partie p;
  init(p, argv[1]);
  mancheJeu(p);
}
