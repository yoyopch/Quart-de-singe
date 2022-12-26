#include "robot.h"
#include "dico.h"
#include "partie.h"
#include "Header.h"

#pragma warning(disable: 4996)


/**
 * @brief Rendre un mot pour le robot si le joueur précédent a entré '?'
 */
void trouve_Dico_Robot(Dico& idico, Partie& partie) {
  //ifstream in("ods4.txt"); // on ouvre le fichier
  //char motDico[MAX_CHAR];
  //in >> setw(MAX_CHAR) >> motDico;
  //while (strlen(motDico) <= 2) in >> setw(MAX_CHAR) >> motDico;
  int i = 0;
  for (i = 0; i < idico.tailleDico; ++i) {
    if (strncmp(idico.mots[i], partie.mot, partie.taillemot) == 0) {
      resetMotJoueur(partie);
      strcpy(partie.motJoueurDeviner, idico.mots[i]);
      cout << idico.mots[i] << endl;
      return;
    }
  }
  if (i == idico.tailleDico) {
    resetMotJoueur(partie);
    strcpy(partie.motJoueurDeviner, partie.mot);
    cout << partie.mot << endl;
  }

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



/**
 * @brief Fonction qui renvoie un chiffre en fonction du robot... ( a completer).
 */
int LettreRobot(Dico& idico, Partie& partie, unsigned int indice, int& indexmotdudico) {
  if (partie.taillemot == 0) {
    LettreAleatoireRobot(partie);
    return 0;
  }
  int num = trouve_mot_DICO(idico, partie, indexmotdudico);
  if (num == 0) {
    cout << partie.motRobot[0] << endl;
    ajoutLettre(partie);
  }
  else {
    cout << "?" << endl;
  }
  return num;

}






int trouve_mot_DICO(Dico& idico, Partie& partie, int& indexmotdudico) {

  int i = indexmotdudico;
  while (i < idico.tailleDico) {
    if (strlen(idico.mots[i]) > partie.taillemot) {
      char* motDico = new char[partie.taillemot + 1];
      strncpy(motDico, idico.mots[i], partie.taillemot);
      if (strncmp(motDico, partie.mot, partie.taillemot) == 0) {
        indexmotdudico = i;

        if (TRACE)
          cout << "motDico = " << motDico << " indexmotdudico: " << indexmotdudico << endl;
        unsigned int Compteur = 0;

        char* listeLettre = new char[MAX_CHAR];
        resetListeLettre(listeLettre);

        int motExiste = verifDebutMot(idico, partie, motDico, Compteur, listeLettre);
        delete[] listeLettre;

        if (motExiste && motDico) {
          delete[] motDico;
          return 0;
        }
        else {
          delete[] motDico;
          return 0;
        }
      }
      delete[] motDico;
    }
    i++;
  }
  return 1;   // return 1 si le mot existe pas
}



void resetListeLettre(char* listeLettre) {
  for (int i = 0; i < MAX_CHAR; ++i) {
    listeLettre[i] = CHAINE_VIDE;
  }
}


int VerifLettreUtil(char lettre, char* listeLettre) {
  for (int i = 0; i < MAX_CHAR; ++i) {
    if (listeLettre[i] == lettre) {
      return 1;
    }
  }
  return 0;
}



int AjoutLettreUtil(char lettre, char* listeLettre) {

  unsigned int i = 0;
  while (listeLettre[i] != CHAINE_VIDE) {
    i++;
  }
  if (VerifLettreUtil(lettre, listeLettre)) {
    return 1;
  }
  else {
    listeLettre[i] = lettre;


    if (TRACE)
      cout << "AjoutLettreUtil lettre : " << lettre  << " et index : " << i << endl;


    return 0;
  }

}






int verifDebutMot(Dico& idico, Partie& partie, char mot[], unsigned int& nbNombre, char* listeLettre) {


  unsigned int oreturn = 0;
  char lettreRand = 'A' + rand() % MAX_CHAR;
  int lettreExiste = AjoutLettreUtil(lettreRand, listeLettre);


  if (TRACE)
    cout << "verifDebutMot lettreRand = " << lettreRand << " et nbNombre = " << nbNombre << endl;

  int nbRand = 0;


  // lettreExiste == 1 si la lettre a deja été générée
  while (lettreExiste) {
    if (nbRand == MAX_CHAR)
      return 1;
    lettreRand = 'A' + rand() % MAX_CHAR;
    nbRand++;
    lettreExiste = AjoutLettreUtil(lettreRand, listeLettre);


    if (TRACE)
      cout << "verifDebutMot lettreExiste = " << lettreRand << endl;

  }



  mot[partie.taillemot] = lettreRand;
  partie.motRobot[0] = lettreRand;

  if (nbNombre == MAX_CHAR)
    return 1;



  unsigned int motExiste = motDebutExiste(idico, partie, mot);
  // voir si il y a un mot dans le dictionnaire qui commencence par "mot"
  if (motExiste) {

    if (TRACE)
      cout << "verifDebutMot motDebutExiste motExiste =" << motExiste << endl;

    int motTrouve = trouve_Dico(idico, mot);
    if (motTrouve) {



      if (TRACE)
        cout << "verifDebutMot motTrouve  trouve_Dico =" << motTrouve << endl;



      nbNombre++;
      oreturn = verifDebutMot(idico, partie, mot, nbNombre, listeLettre);
    }
    else {

      if (TRACE)
        cout << "verifDebutMot return = " << 1 << endl;

      return 1;
    }
  }
  else {
    nbNombre++;
    oreturn = verifDebutMot(idico, partie, mot, nbNombre, listeLettre);
  }


  if (TRACE)
    cout << "verifDebutMot oreturn =" << oreturn << endl;

  return oreturn;

}