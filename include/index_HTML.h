const char INDEX_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
    <title>Simple Messenger on Web</title>
    
    <style>
      body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}
      p {font-size: 15px;color: #444444;margin-bottom: 10px;}
    </style>
    
    <script language="javascript">
        
        function update() {
            var empty = false; // checks whether the input field is empty
            var currentDate = new Date();
            var currentTime = currentDate.toLocaleTimeString();
        
            var userName = document.getElementById("name").value;  // get user's name
            var message = document.getElementById("message").value; // get user's message
        
            if (message == "") {
                empty = true; // if user has no message, don't send
            }
            else if (userName == "") {
                alert("Enter a name so others know who is talking ;)");
                empty = true;
            }

            var mylist = document.getElementById('messagelist');  // get the list element
            
            if (empty == false) {
                // create the message as follows: (NAME at TIME) MESSAGE
                var outMessage = "<li> (" + userName + " at " + currentTime + ") " + message + "</li>";
                mylist.insertAdjacentHTML('beforeend', outMessage); // insert message to the list
                document.getElementById("messageForm").reset(); 
            }
        }

        function seeRocket() {
            var currentDate = new Date();
            var currentTime = currentDate.toLocaleTimeString();
            var userName = document.getElementById("name").value;  // get user's name

            if (userName == "") {
                alert("Enter a name so others know who saw the rocket!");
            }
            else {
                var mylist = document.getElementById('messagelist');  // get the list element
                mylist.insertAdjacentHTML('beforeend', "<li> (" + userName + " at " + currentTime + ") I SEE THE ROCKET!!</li>"); // insert message to the list
            }
        }

    </script>

    <script>
         var x = setInterval(function() {loadData("data.txt",updateData)}, 1000)
         function loadData(url, callback){  
            var xhttp = new XMLHttpRequest();  
            xhttp.onreadystatechange = function(){  
                if(this.readyState == 4 && this.status == 200){  
                    callback.apply(xhttp);  
                }  
            };  
            xhttp.open("GET", url, true);  
            xhttp.send();  
         }  
         function updateData(){  
             document.getElementById("data").innerHTML = this.responseText;  
         }  
    </script>

</head>

<body>
    <h1 align="center">Simple Messenger</h1>
    <form>
        <label for="name">Your Name:</label>
            <input id="name" type="text" placeholder="Your name here..." />
    </form>
    
    <!--
    <p>I'm a noob...so you have to press "send" to send your message :(</p>
    <p>Start of conversation...Let's find a rocket!</p>
    <br>
    -->
    
    <ul id="messagelist">
    </ul>

    <form id="messageForm" onsubmit="return false">
        <input id="message" class="qty" type="text" placeholder="message..." />
        <br><br>
        <input type="button" value="Send Message" onclick="update();" style="margin:auto; height:40px; width:150px;" />
    </form>

    <br><br>
    
    <form>
        <input type="button" value="I see the rocket" onclick="seeRocket();" style="background-color:yellow;margin:auto; height:40px; width:300px;" />
    </form>
    <hr />
    <p align="center">Various Data:</p>
    <p id="data">init</p>
    
</body>

</html>
)=====";