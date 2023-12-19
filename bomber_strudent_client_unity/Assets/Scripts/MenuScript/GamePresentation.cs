using UnityEngine.UI;
using UnityEngine;

public class GamePresentation : MonoBehaviour
{
    public Text textNom;
    public Text textNbJoueur;

    public void setNom(string nom)
    {
        this.textNom.text = "Nom: " + nom;
    }

    public void setNbJoueur(int nbJoueur)
    {
        this.textNbJoueur.text = "Nombre actuel de joueurs : " + nbJoueur;
    }
}
