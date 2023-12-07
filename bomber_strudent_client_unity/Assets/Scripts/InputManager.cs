using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InputManager : MonoBehaviour
{
   

    private BombType chosenBomb=BombType.classic;
    public MessageSender messageSender;
    public BombCount bombCount;


    private void Awake()
    {
        this.messageSender = this.GetComponent<FalseMessageSender>();
        if(this.messageSender != null)
        {
            Debug.Log("ok");
        }
        else
        {
            Debug.Log("ko");
        }
    }
    private void Update()
    {
        getMove();
        getAction();
    }

    private void getMove()
    {

        if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            messageSender.Up();
        }
        else if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            messageSender.Down();

        }
        else if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            messageSender.Left();

        }
        else if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            messageSender.Right();

        }
    }

    private void getAction()
    {
        if (Input.GetKeyDown(KeyCode.Z))
        {
            messageSender.PlaceBomb(chosenBomb);

        }else if (Input.GetKeyDown(KeyCode.X))
        {
            Debug.Log("x");
        }else if (Input.GetKeyDown(KeyCode.Tab))
        {
            chosenBomb = (BombType)((int)(chosenBomb + 1) %3);
            bombCount.selectBomb(chosenBomb);
            Debug.Log(chosenBomb.ToString());
        }
    }
}
