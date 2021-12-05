# Programming 3 project: LOL: win you Runeterra

Team members:  
The Anh Nguyen  
Thuy Phuong Nhi Tran  

## Game story
Once upon the time, under the ruler of The King Aurelion Sol, The nine Realms (Freljord, Demacia, Noxus, Shurima, Targon Mount, Bilgewater, Ionia, Shadow Isles) of Runeterra peacefully coexist.  
One day, in order to remain the peaceful of Runeterra, The King Aurelion Sol has a fight with mysterious creature from the Void and made a heroic sacrifice. The Runeterra now in chaos as the councilor in The Realms starts preparing army to invade the other Realms.  
Witnessing people misleading, The Creator of Runeterra, Riot, informs to everyone in the Runeterra: "If anyone can unify The nine Realms without war, this person can gain unlimited power and be the new The King of Runeterra."   
The players, you are the savers for The Runeterra, however each of you have different approach. Therefore, you are fighting with each other to gain unity to the Realms. Each of you will begin with one assistant. The assistant acted as agent can be sent to one location that you can gain more influence the for one kingdom. The agent can gain more connection to the councilor, however when the assistant is sent to another kingdom, you will lose the connection to the previous kingdom. If lucky enough, you can find more assistant when visiting one kingdom. When you gain enough influence and connection to the councilor and the people in one kingdom, this kingdom will be by our side to help you in the way the be the new The new King of Runeterra.  
BE CAREFUL! You cannot know the others influence and connection as this is there secret plan, so call the assistant back to you if you think that you cannot gain enough influence or connection to this kingdom. If someone has one kingdom by them side, your assistant will be captured and you cannot do any action in this kingdom.  
When the time is running out or the players have no assistants, except one person, this person will be The new King of Runeterra and gain unlimited power from God Riot.  
Good luck all to you!

## Game rule

When execute the program, players are shown a greeting dialog with a brief backstory and basic instructions. In this dialog, the players are able to change the game setting. 
The game start when the player press START button. The game board is initialized with 4 rows and 7 columns of slots. The first row is reserved for the councilors and agents of the current location. The next two rows are reseved for the cards from deck of the current location. The last row is reserved for the agent cards that the current player has. 
Next, the player need to choose the location that they want to perform actions. The game board and the cards will be updated when the location is changed.
In one turn, the player can send agents however they like. However, they can only perform one action only and only when they have an agent sent to current locations. The action to perform is chosen from an dropdown menu after the player have chosen the location and sent an agent. There are four actions that can be performed.  
- Strengthen connections: the agent sent to the location gain more conections that required to own the location.  
- Suffle and draw: the player randomly draw a card from the deck of current location. The drawn card can be an agent card which allows the player have more choices to perform actions from multiple locations, or an influence card which gain influence to the councilor of the current location. After drawing the card, there will be a dialog shows further information of the drawn card.  
- Own area: the player set ownership on the councilor of the current location after gaining enough influence and the agent sent on this location gain enough connection. Then all the cards on the deck will be drawn to the owner.  
- Withdraw agent: player lift the agent sent to location back to their hand.  
After performing an action successfully, the turn will be pass to the next player.  

The player can hover on the cards to see additional details of the card. The player can press the Card bag to check the drawn influence cards gained from current location at anytime.  
The game will finish after an amount of time chosen by the players from the begining or until only one player left has playable agent cards. The winner will be chosen based on total influence on all locations.

