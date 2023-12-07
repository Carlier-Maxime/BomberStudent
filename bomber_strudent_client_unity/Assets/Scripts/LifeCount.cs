using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LifeCount : MonoBehaviour
{
    public Text text;
    public void setHp(int hp)
    {
        text.text = "Points de vie: " + hp;
    }
}
