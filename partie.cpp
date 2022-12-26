#include "partie.h"
#include "affichage.h"
#include "robot.h"
#include "dico.h"



#pragma warning(disable: 4996)



void EffacerJeu(Dico& idico, Partie& partie) {
  detruireJeu(partie);
  freeDico(idico);
}

void AfficheGameOver() {
  cout << "La partie est finie" << endl;
}

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
  if (TRACE)
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









/**
 * @brief initialiser lors d'une nouvelle manche.
 */
void nouvelleManche(Dico& idico, Partie& partie) {
  for (unsigned int i = 0; i < MAX_CHAR; i++) {
    partie.mot[i] = CHAINE_VIDE;
    partie.taillemot = 0;
  }

  if (partie.dernierJoueurPerdant + 1 > 1) {
    int indexmotdudico = 0;
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
      affichageTexte(partie);
      cout << ") > ";
      int letter = 0;
      if (partie.ordre[i] == HUMAIN)
        letter = ajoutLettre(partie, i);
      else {
        letter = LettreRobot(idico, partie, i, indexmotdudico);
      }
      switch (letter) {
      case 0:
        if (trouve_Dico(idico, partie.mot)) {
          afficheMotExiste(idico, partie, i, partie.mot);
          nouvelleManche(idico, partie);
        }
        break;
      case 1:
        // si le joueur a entré '?'
        // saisirMotHumain renvoie la chaine de caractères écrit par le joueur
        saisirMotHumain(idico, partie, i);
        if (verifMot(partie, partie.motJoueurDeviner, i)) {
          debutMotFaux(idico, partie, i, partie.motJoueurDeviner);
          nouvelleManche(idico, partie);
        }
        else if (trouve_Dico(idico, partie.motJoueurDeviner)) {
          if (i == 0)
            afficheMotExiste(idico, partie, partie.nbJoueurs - 1, partie.motJoueurDeviner);
          else
            afficheMotExiste(idico, partie, i, partie.motJoueurDeviner);
          nouvelleManche(idico, partie);
        }
        else {
          AffichemotExistePas(idico, partie, i, partie.motJoueurDeviner);
          nouvelleManche(idico, partie);
        }
        break;
      case 2:
        //si le joueur a entré '!'
        abandonJoueur(idico, partie, i);
        nouvelleManche(idico, partie);
        break;
      }



    }
    // on met le bool a vrai
  }
  if (TRACE)
    cout << "nouvelleMacnhe : " << partie.nouveauTour << endl;
  partie.nouveauTour = VRAI;
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
 * @brief Determine le type de joueurs.
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
      affichageTexte(partie);
      cout << ") > ";

      int letter = 0;
      if (partie.ordre[i] == HUMAIN)
        letter = ajoutLettre(partie, i);
      else {

        if (TRACE)
          cout << "mancheJeu lettreRobot index: " << partie.ordre[i] << endl;

        letter = LettreRobot(idico, partie, i, indexmotdudico);
      }
      switch (letter) {
      case 0:

        if (trouve_Dico(idico, partie.mot)) {
          afficheMotExiste(idico, partie, i, partie.mot);
          nouvelleManche(idico, partie);
        }
        break;
      case 1:
        // si le joueur a entré '?'
        // saisirMotHumain renvoie la chaine de caractères écrit par le joueur
        saisirMotHumain(idico, partie, i);
        // reaffecte partie.motJoueurDeviner
        if (verifMot(partie, partie.motJoueurDeviner, i)) {
          debutMotFaux(idico, partie, i, partie.motJoueurDeviner);
          nouvelleManche(idico, partie);
        }
        else if (trouve_Dico(idico, partie.motJoueurDeviner)) {
          if (i == 0)
            afficheMotExiste(idico, partie, partie.nbJoueurs - 1, partie.motJoueurDeviner);
          else
            afficheMotExiste(idico, partie, i, partie.motJoueurDeviner);

          nouvelleManche(idico, partie);
        }
        else {
          AffichemotExistePas(idico, partie, i, partie.motJoueurDeviner);
          nouvelleManche(idico, partie);
        }
        break;
      case 2:
        //si le joueur a entré '!'
        abandonJoueur(idico, partie, i);
        nouvelleManche(idico, partie);
        break;

      }




    }
  }
}









void resetMotJoueur(Partie& partie) {
  for (unsigned int i = 0; i < MAX_CHAR; ++i)
    partie.motJoueurDeviner[i] = CHAINE_VIDE;
}





void detruireJeu(Partie& partie) {
  delete[] partie.ordre;
  delete[]partie.score;
}





/**
 * @brief vérifier si le mot formé existe.
 */
void saisirMotHumain(Dico& idico, Partie& partie, unsigned int indice) {
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
    for (int i = 0; i < strlen(trouve_mot); ++i) {
      partie.motJoueurDeviner[i] = trouve_mot[i];
    }
    return;
  }
  else {
    trouve_Dico_Robot(idico, partie);
    return;
  }
}
