#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <Keyboard.hpp>
#include <cmath>
#include <cstdlib>
#include<vector>


using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 592), "Glen's Project");
    sf::CircleShape shape(100.f);
    window.setVerticalSyncEnabled (true);

    shape.setFillColor(sf::Color::Green);
    sf::Texture texture,space,fire,boom,boom2,boom3,bombexplosion,powerup1,powerup2;
    space.loadFromFile("space.png");
    fire.loadFromFile("fire.png");
    boom.loadFromFile("bomb.png");
    boom2.loadFromFile("bomb2.png");
    boom3.loadFromFile("bomb3.png");
    bombexplosion.loadFromFile("explosion.png");
    powerup1.loadFromFile("movespeed.png");
    powerup2.loadFromFile("increase.png");



    texture.loadFromFile("800x592.png");
    texture.setSmooth(true);
    space.setSmooth(true);
    fire.setSmooth(true);
    boom.setSmooth(true);
    sf::Sprite sprite(texture),bomb(boom),explosionSprite(bombexplosion),movement(powerup1),increase(powerup2);

    sf::CircleShape playerOne(7),playerTwo(7);
    bomb.setScale(0.0625,0.0625);
    movement.setScale(0.08,0.08);
    movement.setPosition(1050,1050);
    increase.setPosition(1050,1050);
    increase.setScale(0.0625,0.0625);
    explosionSprite.setScale(0.04444444,0.04558405);

    /*vector<sf::Sprite> numOfBombs;
    for(int i = 0;i < 800;i++)
    {
        numOfBombs.push_back(bomb);
        numOfBombs[i].setPosition(1000,1000);
    }
    */
    sf::Sprite numOfBombs[800];
    for(int i =0;i<800; ++i)
    {
        numOfBombs[i]=bomb;
        numOfBombs[i].setPosition(1000,1000);
    }

    sf::Sprite explosion[5000];
    for(int i = 0; i <5000;++i)
    {
        explosion[i]=explosionSprite;
        explosion[i].setPosition(1200,1200);
    }


    vector<bool> check;
    playerOne.setTexture(&space);
    playerTwo.setTexture(&fire);


    int oneX = 240, oneY = 288, twoX = 560, twoY = 288;

    playerOne.setPosition(oneX,oneY);
    playerTwo.setPosition(twoX,twoY);



    bool upArrow = false;
    bool downArrow = false;
    bool leftArrow = false;
    bool rightArrow = false;
    bool upW = false;
    bool leftA = false;
    bool downS = false;
    bool rightD = false;
    //bool bomb1 = false;
    //bool bomb2 = false;

    sf::Clock clock,clock2,bombClock[800],explosionClock[5000],rewardClock1,rewardClock2;
    sf::Time time,time2,bombTime[800],explosionTime[5000],rewardTime1,rewardTime2;


    bool alive = false, alive2 =false;



    int number = 0,whoseBomb[800],explosionNumber=0;
    double speedOne = 0.08,speedTwo = 0.08;
    for(int i = 0; i<800;++i)
    {
        whoseBomb[i]=0;
    }

    bool onfield[800];
    for(int i = 0;i < 800;++i)
        onfield[i]=false;
    bool destruction[10000];
    for(int i = 0;i < 800;++i)
        destruction[i]=false;


    int ammoOne = 5, ammoTwo = 5, bombsAliveOne = 0, bombsAliveTwo = 0;

   bool occupied[50][37];
   for(int j = 0; j < 37; ++j)
    for(int i = 0; i < 50; ++i)
             occupied[i][j] = false;
    //bool empty[1850];

    //Array to create a grid for empty spots. First method used but gave up. Seems too long.
    /*sf::Vertex grid[1850];
    int box=0;
    for(int y = 0; y<=576;y=y+16)
        for(int x = 0;x <=784; x= x+16)
        {
            grid[box].position=sf::Vector2f(x,y);
            empty[box]=true;
            ++box;
        }
    */



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();



        window.draw(sprite);

        //checks if the keyboard has been pressed to create bombs and their position
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && onfield[number]==false && bombsAliveOne <= ammoOne && occupied[oneX/16][oneY/16]==false)
        {
            onfield[number]=true;
            numOfBombs[number].setPosition(playerOne.getPosition());
            whoseBomb[number]=1;
            ++bombsAliveOne;
            for(int y = 0; y < 37 ;++y)
                for(int x = 0; x <50; ++x)
                    for(int i = 0; i <800; ++i)
                        if(numOfBombs[i].getPosition()==sf::Vector2f(x*16,y*16))
                        {
                            //std::cout<<"there is a bomb at "<<x<<"and "<< y<<" " <<i<<endl;
                            occupied[x][y]=true;


                        }
            bombClock[number].restart();
           // bombTime[number]=bombClock[number].getElapsedTime();




            ++number;
            std::cout<<bombsAliveOne<<endl;

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && onfield[number]==false && bombsAliveTwo <= ammoTwo && occupied[twoX/16][twoY/16]==false)
        {
            onfield[number]=true;
            numOfBombs[number].setPosition(playerTwo.getPosition());
            whoseBomb[number]=2;
            ++bombsAliveTwo;
            for(int y = 0; y < 37 ;++y)
                for(int x = 0; x <50; ++x)
                    for(int i = 0; i <800; ++i)
                        if(numOfBombs[i].getPosition()==sf::Vector2f(x*16,y*16))
                        {
                            //std::cout<<"there is a bomb at "<<x<<"and "<< y<<" " <<i<<endl;
                            occupied[x][y]=true;


                        }
            bombClock[number].restart();
            ++number;
            std::cout<<bombsAliveTwo<<endl;

        }

        //for loop to create bombs on the field that are alive
        for(int i = 0;i<800;++i)
            if(onfield[i]==true)
            {
                window.draw(numOfBombs[i]);

            }


        for(int i = 0; i <800; ++i)
        {
            bombTime[i]=bombClock[i].getElapsedTime();
            if(bombTime[i].asSeconds()> 1.5 && whoseBomb[i]>0)
            {
                numOfBombs[i].setTexture(boom2);
            }
            if(bombTime[i].asSeconds()> 2.5 && whoseBomb[i]>0)
            {
                numOfBombs[i].setTexture(boom3);
            }


            if(bombTime[i].asSeconds()> 3.5 && whoseBomb[i]>0)
            {

                sf::Vector2f v1(numOfBombs[i].getPosition());
                int xCoor = v1.x/16,xExpo=v1.x,xExpo1=v1.x;
                int yCoor = v1.y/16,yExpo=v1.y,yExpo1=v1.y,yExpo2=v1.y;

                numOfBombs[i].setPosition(1000,1000);
                numOfBombs[i].setTexture(boom);
                occupied[xCoor][yCoor]= false;



                for(int i = 0;i<200;++i)
                {
                    if(i<50 )
                    {
                    explosion[explosionNumber].setPosition(xExpo,yExpo);
                    yExpo=yExpo-16;

                    }
                if(i>=50 && i<100)
                {
                explosion[explosionNumber].setPosition(xExpo,yExpo1);
                yExpo1=yExpo1+16;


                }
                if(i>=100 && i<150)
                {
                explosion[explosionNumber].setPosition(xExpo,yExpo2);
                xExpo=xExpo-16;

                }
                if(i>=150 && i<200)
                {
                explosion[explosionNumber].setPosition(xExpo1,yExpo2);
                xExpo1=xExpo1+16;
                }

                explosionClock[explosionNumber].restart();
                destruction[explosionNumber]=true;




                //if the explosion lands on one of the players, ends the game
                if(explosion[explosionNumber].getPosition()==playerTwo.getPosition())
                {
                    sf::RenderWindow endScreen(sf::VideoMode(700,300),"End");
                    sf::Font font;
                    font.loadFromFile("arialbi.ttf");
                    sf::Text Victory1,Victory2,Victory3;
                    Victory1.setString("Player Two has died! Player One is the Victor!");
                    Victory1.setFont(font);
                    Victory1.setCharacterSize(20);
                    Victory1.setPosition(125,0);
                    Victory2.setFont(font);
                    Victory2.setCharacterSize(20);
                    Victory2.setString("Press enter to restart!");
                    Victory2.setPosition(220,100);
                    Victory3.setFont(font);
                    Victory3.setCharacterSize(20);
                    Victory3.setString("Press escape to close!");
                    Victory3.setPosition(220, 130);



                    while(endScreen.isOpen())
                    {
                        sf::Event endEvent;
                        while (endScreen.pollEvent(endEvent))
                        {
                            if (endEvent.type == sf::Event::Closed)
                                endScreen.close();
                        }
                        endScreen.clear();
                        endScreen.draw(Victory1);
                        endScreen.draw(Victory2);
                        endScreen.draw(Victory3);
                        endScreen.display();
                        //give options to restart or close
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                        {
                             ammoOne = 5, ammoTwo = 5, bombsAliveOne = 0, bombsAliveTwo = 0,speedOne=0.08,speedTwo=0.08;
                             oneX = 240, oneY = 288, twoX = 560, twoY = 288;

                                 playerOne.setPosition(oneX,oneY);
                                 playerTwo.setPosition(twoX,twoY);
                                 number = 0;
                                 for(int i = 0; i<800;++i)
                                 {
                                     whoseBomb[i]=0;
                                 }
                                 for(int i = 0;i < 800;++i)
                                     onfield[i]=false;
                                 for(int i = 0;i < 800;++i)
                                     destruction[i]=false;
                                 for(int j = 0; j < 37; ++j)
                                  for(int i = 0; i < 50; ++i)
                                           occupied[i][j] = false;
                                 for(int i = 0; i <5000;++i)
                                 {
                                     explosion[i]=explosionSprite;
                                     explosion[i].setPosition(1200,1200);
                                 }
                                 //numOfBombs.clear();
                                 for(int i = 0;i < 800;i++)
                                 {
                                     //numOfBombs.push_back(bomb);
                                     numOfBombs[i].setPosition(1000,1000);
                                 }
                                 for(int i =0; i<5000;++i)
                                 {
                                     explosion[i].setPosition(1200,1200);
                                 }
                                 for(int i =0;i<800;++i)
                                 {
                                     destruction[i]=false;
                                 }
                                 movement.setPosition(1050,1050);
                                 alive=false;
                                 alive2=false;
                                 increase.setPosition(1050,1050);
                                 endScreen.close();
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        {
                            endScreen.close();
                            window.close();
                        }

                    }

                }
                if(explosion[explosionNumber].getPosition()==playerOne.getPosition())
                {
                    sf::RenderWindow endScreen(sf::VideoMode(700,300),"End");
                    sf::Font font;
                    font.loadFromFile("arialbi.ttf");
                    sf::Text Victory1,Victory2,Victory3;
                    Victory1.setString("Player One has died! Player Two is the Victor!");
                    Victory1.setFont(font);
                    Victory1.setCharacterSize(20);
                    Victory1.setPosition(125,0);
                    Victory2.setFont(font);
                    Victory2.setCharacterSize(20);
                    Victory2.setString("Press enter to restart!");
                    Victory2.setPosition(220,100);
                    Victory3.setFont(font);
                    Victory3.setCharacterSize(20);
                    Victory3.setString("Press escape to close!");
                    Victory3.setPosition(220, 130);


                    while(endScreen.isOpen())
                    {
                        sf::Event endEvent;
                        while (endScreen.pollEvent(endEvent))
                        {
                            if (endEvent.type == sf::Event::Closed)
                                endScreen.close();
                        }
                        endScreen.clear();
                        endScreen.draw(Victory1);
                        endScreen.draw(Victory2);
                        endScreen.draw(Victory3);
                        endScreen.display();
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                        {
                             ammoOne = 5, ammoTwo = 5, bombsAliveOne = 0, bombsAliveTwo = 0;
                             oneX = 240, oneY = 288, twoX = 560, twoY = 288;

                                 playerOne.setPosition(oneX,oneY);
                                 playerTwo.setPosition(twoX,twoY);
                                 number = 0;
                                 for(int i = 0; i<800;++i)
                                 {
                                     whoseBomb[i]=0;
                                 }
                                 for(int i = 0;i < 800;++i)
                                     onfield[i]=false;
                                 for(int i = 0;i < 800;++i)
                                     destruction[i]=false;
                                 for(int j = 0; j < 37; ++j)
                                  for(int i = 0; i < 50; ++i)
                                           occupied[i][j] = false;
                                 for(int i = 0; i <5000;++i)
                                 {
                                     explosion[i]=explosionSprite;
                                     explosion[i].setPosition(1200,1200);
                                 }
                                 //numOfBombs.clear();
                                 for(int i = 0;i < 800;i++)
                                 {
                                     //numOfBombs.push_back(bomb);
                                     numOfBombs[i].setPosition(1000,1000);
                                 }
                                 for(int i =0; i<5000;++i)
                                 {
                                     explosion[i].setPosition(1200,1200);
                                 }
                                 for(int i =0;i<800;++i)
                                 {
                                     destruction[i]=false;
                                 }
                                 movement.setPosition(1050,1050);
                                 alive=false;
                                 alive2=false;
                                 increase.setPosition(1050,1050);
                                 endScreen.close();
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        {
                            endScreen.close();
                            window.close();
                        }

                    }

                }

                ++explosionNumber;



                }


                if(whoseBomb[i]=1 && bombsAliveOne>0 && onfield[i]==true)
                {

                    whoseBomb[i]=0;
                    onfield[i]=false;




                    bombsAliveOne = bombsAliveOne-1;

                }
                if(whoseBomb[i]=2 && bombsAliveTwo>0 && onfield[i]==true)
                {

                    whoseBomb[i]=0;
                    onfield[i]=false;




                    bombsAliveTwo = bombsAliveTwo-1;

                }


            }
         }

        for(int i = 0;i<5000;++i)
        {
            explosionTime[i]=explosionClock[i].getElapsedTime();
            if(destruction[i]==true && explosionTime[i].asSeconds() < 0.5)
            {
                window.draw(explosion[i]);

            }
            if(destruction[i]==true && explosionTime[i].asSeconds() >= 0.5)
            {
                destruction[i]=false;
                explosion[i].setPosition(1200,1200);

            }

        }

        //powerups here

        rewardTime1=rewardClock1.getElapsedTime();
        rewardTime2=rewardClock2.getElapsedTime();
        //if player is on top of buff
        if(movement.getPosition()==playerOne.getPosition() && alive == true)
        {
            speedOne = speedOne - 0.005;
            movement.setPosition(1050,1050);
            alive =false;
            rewardClock1.restart();
        }
        if(movement.getPosition()==playerTwo.getPosition() && alive == true)
        {
            speedTwo= speedTwo - 0.005;
            movement.setPosition(1050,1050);
            alive = false;
            rewardClock1.restart();
        }
        if(increase.getPosition()==playerOne.getPosition()&& alive2 == true)
        {
            ammoOne =ammoOne + 2;
            increase.setPosition(1050,1050);
            alive2 = false;
            rewardClock2.restart();
        }
        if(increase.getPosition()==playerTwo.getPosition()&& alive2 == true)
        {
            ammoTwo = ammoTwo + 2;
            increase.setPosition(1050,1050);
            alive = false;
            rewardClock2.restart();
        }

        if(rewardTime1.asSeconds() >10 && alive==false)
        {
            int x1 = (rand()% 50)*16;
            int y1 = (rand() % 37)*16;
            movement.setPosition(x1,y1);
            alive=true;
        }
        if(rewardTime2.asSeconds() > 10 && alive2==false)
        {
            int x2 = (rand()% 50)*16;
            int y2 = (rand() % 37)*16;
            increase.setPosition(x2,y2);
            alive2=true;
        }



        if(alive==true)
            window.draw(movement);
        if(alive2==true)
            window.draw(increase);


        window.draw(playerOne);
        window.draw(playerTwo);

        window.display();

       time = clock.getElapsedTime();
       time2 = clock2.getElapsedTime();


        //First method for figuring out keypresses. Objects would not move at the same time so this method is thrown away.
       /* if(event.type == sf::Event::KeyPressed && time2.asSeconds()>=.05)
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Up: upArrow=true;
                break;
                case sf::Keyboard::Down: downArrow = true;
                break;
                case sf::Keyboard::Left: leftArrow = true;
                break;
                case sf::Keyboard::Right: rightArrow = true;
                break;




                default : break;
            }
        }
*/



       //possible moves list
       //sf::Vector2f up1,up2,down1,down2,right1,right2,left1,left2;
       sf::Vector2f left1(oneX-16,oneY);
       sf::Vector2f left2(twoX-16,twoY);
       sf::Vector2f right1(oneX+16,oneY);
       sf::Vector2f right2(twoX+16,twoY);
       sf::Vector2f up1(oneX,oneY-16);
       sf::Vector2f up2(twoX,twoY-16);
       sf::Vector2f down1(oneX,oneY+16);
      sf::Vector2f down2(twoX,twoY+16);

      sf::Vector2f real1(oneX,oneY);
      sf::Vector2f real2(twoX,twoY);

        //setting up booleans for movement
       if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && time2.asSeconds()>=speedTwo)
       {
           leftArrow=true;
       }
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&& time2.asSeconds()>=speedTwo)
       {
           rightArrow=true;
       }
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& time2.asSeconds()>=speedTwo)
       {
           upArrow=true;
       }
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& time2.asSeconds()>=speedTwo)
       {
           downArrow=true;
       }

       if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && time.asSeconds()>=speedOne)
       {
           leftA=true;
       }
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)&& time.asSeconds()>=speedOne)
       {
           rightD=true;
       }
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)&& time.asSeconds()>=speedOne)
       {
           upW=true;
       }
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)&& time.asSeconds()>=speedOne)
       {
           downS=true;
       }









        if(upArrow==true && twoY-16 >= 0 && twoY-16 <= 576 && (up2 != playerOne.getPosition()) && occupied[twoX/16][(twoY-16)/16]==false)
        {

            twoY = twoY - 16;
            playerTwo.setPosition(twoX,twoY);
            time2=clock2.restart();



        }
        if(downArrow==true&&twoY+16 >= 0 && twoY+16 <= 576 &&  down2 != playerOne.getPosition() && occupied[twoX/16][(twoY+16)/16]==false)
        {
            twoY = twoY + 16;
            playerTwo.setPosition(twoX,twoY);
            time2=clock2.restart();

        }
        if(rightArrow==true&&twoX+16 >= 0 && twoX+16 <= 784 &&  right2 != playerOne.getPosition() && occupied[(twoX+16)/16][twoY/16]==false)
        {
            twoX = twoX + 16;
            playerTwo.setPosition(twoX,twoY);
            time2=clock2.restart();

        }
        if(leftArrow==true&&twoX-16 >= 0 && twoX-16 <= 784 &&  left2 != playerOne.getPosition() && occupied[(twoX-16)/16][twoY/16]==false)
        {
            twoX = twoX - 16;
            playerTwo.setPosition(twoX,twoY);
            time2=clock2.restart();

        }



        if(upW==true&& oneY-16 >=0 && oneY-16<=576 && up1 != playerTwo.getPosition() && occupied[oneX/16][(oneY-16)/16]==false)
        {
            oneY = oneY - 16;
            playerOne.setPosition(oneX,oneY);
            time=clock.restart();

        }
        if(downS==true&& oneY+16 >=0 && oneY+16<=576 && down1 != playerTwo.getPosition()&& occupied[oneX/16][(oneY+16)/16]==false)
        {
            oneY = oneY + 16;
            playerOne.setPosition(oneX,oneY);
            time=clock.restart();

        }
        if(rightD==true && oneX+16>=0 && oneX+16<=784 && right1 != playerTwo.getPosition()&& occupied[(oneX+16)/16][oneY/16]==false)
        {
            oneX = oneX + 16;
            playerOne.setPosition(oneX,oneY);
            time=clock.restart();

        }
        if(leftA==true&&oneX-16 >=0 && oneX-16<=784 && left1 != playerTwo.getPosition()&& occupied[(oneX-16)/16][oneY/16]==false)
        {
            oneX = oneX - 16;
            playerOne.setPosition(oneX,oneY);
            time=clock.restart();

        }

       /* for(int i = 0; i <800; ++i)
        {
            bombTime[i]=bombClock[i].getElapsedTime();
            if(bombTime[i].asSeconds()> 2.5 && whoseBomb[i]>0)
            {

                sf::Vector2f v1(numOfBombs[i].getPosition());
                int xCoor = v1.x/16;
                int yCoor = v1.y/16;

                numOfBombs[i].setPosition(1000,1000);
                occupied[xCoor][yCoor]= false;

                if(whoseBomb[i]=1 && bombsAliveOne>0 && onfield[i]==true)
                {

                    whoseBomb[i]=0;
                    onfield[i]=false;




                    bombsAliveOne = bombsAliveOne-1;

                }
                if(whoseBomb[i]=2 && bombsAliveTwo>0 && onfield[i]==true)
                {

                    whoseBomb[i]=0;
                    onfield[i]=false;




                    bombsAliveTwo = bombsAliveTwo-1;

                }


            }
         }

*/





        upArrow = false;
       downArrow = false;
        leftArrow = false;
        rightArrow = false;
        upW = false;
        leftA = false;
        downS = false;
        rightD = false;
        std::cout<<number<<" "<<explosionNumber<<endl;
        if(number >750)
            number=0;
        if(explosionNumber>4500)
            explosionNumber=0;

    }

    return 0;
}



