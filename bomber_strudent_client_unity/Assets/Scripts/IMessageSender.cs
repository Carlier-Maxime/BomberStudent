public interface MessageSender
{
    public void Up();
    public void Down();
    public void Left();
    public void Right();

    public void PlaceBomb(BombType bombType);

}
