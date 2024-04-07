# Tibia 8.6 ComboBot

![](https://i.imgur.com/RW4A74w.png)
![](https://i.imgur.com/9h11b1C.png)

### Description

- Tibia 8.6 ComboBot is divided into 2 clients and server. One client is destined for LEADER and another one for TEAMMATES. It's an application that allows for LEADER target the enemy and TEAMMATES of LEADER shoot specific rune at the same time.

### Setup
1. Compile projects remembering to change IP and PORT in solutions- install via vckp or in other way BOOST library (won't compile without it)
2. Go to server and change IP and PORT, `npm install` then `npm start`
3. Run Tibia 8.6
4. LOG IN to your character, MENU (F12) won't show up if you are logged off
4. Leader runs destined client
5. Other teammates runs destined client
6. Press F12 to display menu
7. Set RUNE ID and RUNE DELAY
8. Remember to open BACKPACK with specific RUNE- BACKPACK has to be open both for LEADER and TEAMMATE aswell
8. In game LEADER ATTACKS mob / PLAYER and then press NUM0 (NUMPAD 0) to initiate combo- all TEAMMATES must be near the LEADER and see TARGET.


### Problems
When SERVER is configured- IP and PORT is set- TEAMMATES might not connect successfully to the SERVER. That's because of FIREWALL / PORT. Specific PORT might be closed. In some cases you might want to either disable FIREWALL- which I do not recommend or configure it to allow CLIENT works on specific port. Bot works on LOCAL NETWORK.

### Information
Bot has been written in educational purposes for learning c++, sockets and so on. EXE files and DLL's are 100% clean- they doesn't have any malicious code inside it. At some servers using BOT SOFTWARE are PROHIBITED. Read TOS of server before using that SOFTWARE. I am not responsible for any DAMAGE / LOSS / BAN. You are using that BOT for your own responsibility. If you are not sure if you want to use it, then DON'T
