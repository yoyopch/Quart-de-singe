#include "partie.h"
#include "robot.h"
#include "dico.h"

#pragma warning(disable: 4996)

/**
 * @brief Afficher le score de la partie
 * @param[in] partie : La partie en cours
 * @param[in] indice : Indice du joueur prenant un quart de singe
 */
void afficheScore(const Partie& partie, const unsigned int indice) {
  partie.score[indice] += 0.25;
  for (unsigned int i = 0; i < partie.nbJoueurs - 1; ++i) {
    cout << i + 1 << partie.ordre[i] << " : " << partie.score[i] << "; ";
  }
  cout << partie.nbJoueurs << partie.ordre[partie.nbJoueurs - 1] << " : " << partie.score[partie.nbJoueurs - 1] << endl;
}

/**
 * @brief Afficher le mot formé.
 * @param[in] partie : La partie en cours.
 */
void afficheTexte(const Partie& partie) {
  unsigned int i = 0;
  while (partie.mot[i] != CHAINE_VIDE) {
    cout << partie.mot[i];
    i++;
  }
}

/**
 * @brief Afficher le message d'abandon du joueur .
 * @param[in] partie : La partie en cours.
 * @param[in] indice : Indice du joueur qui abandonne
 */
void afficheAbandonJoueur(Partie& partie, unsigned int indice) {
  if (indice == partie.nbJoueurs)
    indice -= (partie.nbJoueurs - 1);
  cout << "le joueur " << indice + 1 << partie.ordre[indice] << " abandonne la manche et prend un quart de singe" << endl; // si l'utilisateur rentre '!'
  partie.dernierJoueurPerdant = indice;
}

/**
 * @brief Afficher le message disant que le mot saisi n'existe pas
 * @param[in] partie: La partie en cours
 * @param[in] indice : Indice du joueur prenant un quart de singe
 * @param[in] mot : Mot qui n'existe pas dans le dictionnaire.
 */
void AfficheMotExistePas(Partie& partie, unsigned int indice, char mot[]) {
  if (indice + 1 == 1) {
    indice = partie.nbJoueurs;
  }
  cout << "le mot " << mot << " n'existe pas, " << indice << partie.ordre[indice - 1] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice - 1;
}

/**
 * @brief Affiche le message disant que le mot existe dans le dictionnaire
 * @param[in] partie: La partie en cours
 * @param[in] indice : Indice du joueur qui va prendre un quart de singe
 * @param[in] trouve_mot : Mot qui existe dans le dictionnaire.
 */
void afficheMotExiste(Partie& partie, unsigned int indice, const char trouve_mot[]) {

  if (indice == partie.nbJoueurs) {
    indice -= (partie.nbJoueurs);
  }
  cout << "le mot " << trouve_mot << " existe, le joueur " << indice + 1 << partie.ordre[indice] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice;
}

/**
 * @brief Afficher le message disant que le mot saisi ne commence pas par les lettres attendues
 * @param[in] partie: La partie en cours
 * @param[in] indice : Indice du joueur qui prend un quart de singe
 * @param[in] mot : Mot incorrect
 */
void AfficheDebutMotFaux(Partie& partie, unsigned int indice, const char mot[]) {
  if (indice + 1 == 1) indice = partie.nbJoueurs;
  cout << "le mot " << mot << " ne commence pas par les lettres attendues, le joueur " << indice << partie.ordre[indice - 1] << " prend un quart de singe" << endl;
  partie.dernierJoueurPerdant = indice - 1;
}

/**
 * @brief Afficher la fin du jeu.
 */
void AfficheGameOver() {
  cout << "La partie est finie" << endl;
}

/**
 * @brief Desallouer les zones memoires allouees en memoire dynamique
 * @param[in] idico : Le dictonnaire
 * @param[in] partie: La partie en cours .
 */
void EffacerJeu(Dico& idico, Partie& partie) {
  detruireJeu(partie);
  desallouerDico(idico);
}

/**
 * @brief Verifier si un joueur a obtenu quatre quarts de singe
 * @param[in] partie: La partie en cours.
 * @return oreturn : 1 si un joueur a obtenu quatre quarts de singe, sinon 0
 */
unsigned int finduJeu(Partie& partie) {
  unsigned int oreturn = 0;
  for (unsigned int i = 0; i < partie.nbJoueurs; ++i) {
    if (partie.score[i] == 1) {
      oreturn = 1;
      break;
    }
  }
  return oreturn;
}

/**
 * @brief Initialiser les structure
 * @param[in] partie : La partie en cours
 * @parame[in] pl : Chaine de caracteres entree sur la ligne de commande.
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
  partie.nbJoueurs = (unsigned int)strlen(pl);
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
 * @brief Permet a l'humain de jouer et de saisir une lettre ou '?' ou '!'
 * @param[in] partie : La partie en cours
 * @return oreturn : 0 si le joueur a saisi une lettre, 1 si le joueur a saisi '?' ou 2 si le joueur a saisi '!'.
 */
int ajoutLettre(Partie& partie) {

  unsigned int oreturn = 0;
  char mot;
  unsigned int i = 0;

  cin >> mot;
  cin.ignore(INT_MAX, '\n');
  if (TRACE)
    cout << "ajoutLettre mot: " << mot << endl;

  //le joueur a saisi '?'
  if (mot == FINISH1) {
    if (TRACE)
      cout << "ajoutLettre mot == FINISH1" << endl;
    oreturn = 1;
  }
  else
    //le joueur a saisi '!'
    if (mot == FINISH2) {
      if (TRACE)
        cout << "ajoutLettre mot == FINISH2" << endl;
      oreturn = 2;
    }
  if (oreturn == 0) {
    while (partie.mot[i] != CHAINE_VIDE) {
      i++;
    }
    if (TRACE)
      cout << "ajoutLettre i = " << i << endl;

    if (partie.mot[i] == CHAINE_VIDE) {
      partie.mot[i] = toupper(mot);
      partie.taillemot++;
    }
  }

  return oreturn;
}

/**
 * @brief Afficchage et gestion de la nouvelle manche
 * @param[in] idico : Le dictionnaire
 * @param[in] partie : La partie en cours.
 */
void nouvelleManche(Dico& idico, Partie& partie) {
  for (unsigned int i = 0; i < MAX_CHAR; i++) {
    partie.mot[i] = CHAINE_VIDE;
    partie.taillemot = 0;
  }
  int indexmotdudico = 0;

  if (partie.dernierJoueurPerdant + 1 > 1) {
    for (unsigned int i = partie.dernierJoueurPerdant; i < partie.nbJoueurs; ++i) {
      if (partie.nouveauTour == VRAI) {
        i = 0;
        partie.nouveauTour = FAUX;
      }

      if (finduJeu(partie)) {
        EffacerJeu(idico, partie);
        AfficheGameOver();
        exit(0);
      }

      cout << i + 1 << partie.ordre[i] << ", (";
      afficheTexte(partie);
      cout << ") > ";
      int letter = 0;
      if (partie.ordre[i] == HUMAIN)
        letter = ajoutLettre(partie);
      else {
        letter = LettreRobot(idico, partie, i, indexmotdudico);
      }
      switch (letter) {
      case 0:
        if (trouverMotDansDico(idico, partie.mot)) {
          afficheMotExiste(partie, i, partie.mot);
          afficheScore(partie, i);

          indexmotdudico = 0;
          nouvelleManche(idico, partie);
        }
        break;
      case 1:
        // si le joueur a entré '?'
        // saisirMotHumain renvoie la chaine de caractères écrit par le joueur
        saisirMot(idico, partie, i);
        if (verifMot(partie, partie.motJoueurDeviner)) {
          AfficheDebutMotFaux(partie, i, partie.motJoueurDeviner);
          afficheScore(partie, partie.dernierJoueurPerdant);

          indexmotdudico = 0;
          nouvelleManche(idico, partie);
        }
        else if (trouverMotDansDico(idico, partie.motJoueurDeviner)) {
          afficheMotExiste(partie, i, partie.motJoueurDeviner);
          afficheScore(partie, i);

          indexmotdudico = 0;
          nouvelleManche(idico, partie);
        }
        else {
          AfficheMotExistePas(partie, i, partie.motJoueurDeviner);
          afficheScore(partie, partie.dernierJoueurPerdant);

          indexmotdudico = 0;
          nouvelleManche(idico, partie);
        }
        break;
      case 2:
        //si le joueur a entré '!'
        afficheAbandonJoueur(partie, i);
        afficheScore(partie, partie.dernierJoueurPerdant);

        indexmotdudico = 0;
        nouvelleManche(idico, partie);
        break;
      }
    }

  }
  if (TRACE)
    cout << "nouvelleMacnhe : " << partie.nouveauTour << endl;
  // on met le bool a vrai
  partie.nouveauTour = VRAI;
}

/**
 * @brief cherchez si deux mots commencent par les memes lettres
 * @param[in] mot : le mot a compare avec le mot de la partie
 * @return oreturn : 1 si les deux mots ne commencent pas par les memes lettres, sinon 0.
 */
int verifMot(Partie& partie, const char mot[]) {
  unsigned int oreturn = 0;
  for (unsigned int i = 0; i < strlen(partie.mot); ++i) {
    if (partie.mot[i] != mot[i]) {
      oreturn = 1;
      break;
    }
  }
  return oreturn;
}

/**
 * @brief Manche de la partie en cours
 * @param[in] idico : Le dictionnaire
 * @param[in] partie: La partie en cours.
 */
void mancheJeu(Dico& idico, Partie& partie) {
  int indexmotdudico = 0;
  while (partie.taillemot < MAX_CHAR) {
    for (unsigned int i = 0; i < partie.nbJoueurs; ++i) {

      if (TRACE)
        cout << "mancheJeu nouveauTour : " << partie.nouveauTour << endl;

      if (partie.nouveauTour == VRAI) {
        i = 0;
        partie.nouveauTour = FAUX;
      }

      if (finduJeu(partie)) {
        EffacerJeu(idico, partie);
        AfficheGameOver();
        exit(0);
      }

      cout << i + 1 << partie.ordre[i] << ", (";
      afficheTexte(partie);
      cout << ") > ";

      int letter = 0;
      if (partie.ordre[i] == HUMAIN)
        letter = ajoutLettre(partie);
      else {

        if (TRACE)
          cout << "mancheJeu lettreRobot index: " << partie.ordre[i] << endl;

        letter = LettreRobot(idico, partie, i, indexmotdudico);
      }
      switch (letter) {
      case 0:

        if (trouverMotDansDico(idico, partie.mot)) {
          afficheMotExiste(partie, i, partie.mot);
          afficheScore(partie, i);

          indexmotdudico = 0;
          nouvelleManche(idico, partie);
        }
        break;
      case 1:
        // si le joueur a entré '?'
        // saisirMotHumain renvoie la chaine de caractères écrit par le joueur
        saisirMot(idico, partie, i);
        // reaffecte partie.motJoueurDeviner
        if (verifMot(partie, partie.motJoueurDeviner)) {
          AfficheDebutMotFaux(partie, i, partie.motJoueurDeviner);
          afficheScore(partie, partie.dernierJoueurPerdant);

          indexmotdudico = 0;
          nouvelleManche(idico, partie);
        }
        else if (trouverMotDansDico(idico, partie.motJoueurDeviner)) {
          afficheMotExiste(partie, i, partie.motJoueurDeviner);
          afficheScore(partie, i);

          indexmotdudico = 0;
          nouvelleManche(idico, partie);

        }
        else {
          AfficheMotExistePas(partie, i, partie.motJoueurDeviner);
          afficheScore(partie, partie.dernierJoueurPerdant);

          indexmotdudico = 0;
          nouvelleManche(idico, partie);
        }
        break;
      case 2:
        //si le joueur a entré '!'
        afficheAbandonJoueur(partie, i);
        afficheScore(partie, partie.dernierJoueurPerdant);

        indexmotdudico = 0;
        nouvelleManche(idico, partie);
        break;

      }
    }
  }
}

/**
 * @brief Reinitialiser le mot a deviner dans la structure 'partie'
 * @param partie : La partie en cours.
 */
void resetMotJoueur(Partie& partie) {
  for (unsigned int i = 0; i < MAX_CHAR; ++i)
    partie.motJoueurDeviner[i] = CHAINE_VIDE;
}

/**
 * @brief Desallouer les zones memoires allouees en memoire dynamique dans la strucutre 'partie'
 * @param partie : La partie en cours .
 */
void detruireJeu(Partie& partie) {
  delete[] partie.ordre;
  delete[]partie.score;
}

/**
 * @brief Saisir un mot si le joueur précédent a saisi '?'
 * @param[in] idico : Le dictionnaire
 * @param[in] partie : La partie en cours
 * @param[in] indice : Indice du joueur qui doit saisir le mot.
 */
void saisirMot(Dico& idico, Partie& partie, unsigned int indice) {
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
      EffacerJeu(idico, partie);
      exit(0);
    }
    for (unsigned int i = 0; i < strlen(trouve_mot); ++i) {
      trouve_mot[i] = toupper(trouve_mot[i]);
    }
    resetMotJoueur(partie);
    for (unsigned int i = 0; i < strlen(trouve_mot); ++i) {
      partie.motJoueurDeviner[i] = trouve_mot[i];
    }
    return;
  }
  else {
    trouveMotDico_Robot(idico, partie);
    return;
  }
}
