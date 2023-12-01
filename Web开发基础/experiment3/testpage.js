
var today = new Date();

function  getD1()
{
    var d1=today.toLocaleString();
    document.getElementById("datetime").innerHTML =d1; 
}

function bonjour()
{
    var h = today.getHours();
    if(h>=0&&h<12)
    {
        return '早上好！';
    }
    else if(h>=12&&h<18)
    {
        return '下午好！';
    }
    else
    {
        return '晚上好！';
    }
}

var elaspedSeconds = 0;
var elaspedMinutes = 0;
var timer;

function count()
{
    window.addEventListener("load", function(){
        var startTime = Date.now();
        timer = this.setInterval(function(){
            var currentTime = Date.now();
            elaspedSeconds = Math.floor((currentTime - startTime) / 1000) % 60;
            elaspedMinutes = Math.floor((currentTime - startTime) / 1000 / 60);
            document.getElementById("timer").textContent = "已用时：" + elaspedMinutes + "分钟" + elaspedSeconds + "秒";
        },1000)
    })

    var submitbutton = document.getElementById("submitbutton");
    submitbutton.addEventListener("submit",function(){
        clearInterval(timer);
    })
}




function validateForm()
{
    var score = 0;
    var message =" ";
    var nullchoice = [];
    var incorrectanswers = [];
    var partTrueOfCheckbox = [];

    //单选题

    var sinplechoixinput1 = document.getElementsByName("sinchoix1");
    var sinplechoixinput2 = document.getElementsByName("sinchoix2");
    var sinplechoixinput3 = document.getElementsByName("sinchoix3");
    var sinplechoixinput4 = document.getElementsByName("sinchoix4");

    var i = 0;

    //1(1)
    for(i=0;i<4;i++)
    {
        if(sinplechoixinput1[i].checked)
            break;
    }
    if(i === 4)
    {
        nullchoice.push("1(1)");
    }
    else
    {
        var sinchoice1 = document.querySelector('input[name="sinchoix1"]:checked').value;
        if(sinchoice1 === "false")
            incorrectanswers.push("1(1)、应选C");
        else
            score += 2;
    }

    //1(2)
    for(i=0;i<4;i++)
    {
        if(sinplechoixinput2[i].checked)
            break;
    }
    if(i === 4)
    {
        nullchoice.push("1(2)");
    }
    else
    {
        var sinchoice2 = document.querySelector('input[name="sinchoix2"]:checked').value;
        if(sinchoice2 === "false")
            incorrectanswers.push("1(2)、应选B");
        else
            score += 2;
    }

    //2(1)
    for(i=0;i<4;i++)
    {
        if(sinplechoixinput3[i].checked)
            break;
    }
    if(i === 4)
    {
        nullchoice.push("2(1)");
    }
    else
    {
        var sinchoice3 = document.querySelector('input[name="sinchoix3"]:checked').value;
        if(sinchoice3 === "false")
            incorrectanswers.push("2(1)、应选D");
        else
            score += 2;
    }
    
    //2(2)
    for(i=0;i<4;i++)
    {
        if(sinplechoixinput4[i].checked)
            break;
    }
    if(i === 4)
    {
        nullchoice.push("2(2)")
    }
    else
    {
        var sinchoice4 = document.querySelector('input[name="sinchoix4"]:checked').value;
        if(sinchoice4 === "false")
            incorrectanswers.push("2(2)、应选A");
        else
            score += 2;
    }

    //单选题
    //多选题

    var multiplechoixinput1 = document.getElementsByName("mulchoix1");
    var multiplechoixinput2 = document.getElementsByName("mulchoix2");

    //3
    for(i=0;i<multiplechoixinput1.length;i++)
    {
        if(multiplechoixinput1[i].checked)
            break;
    }

    if(i === multiplechoixinput1.length)
    {
        nullchoice.push("3")
    }
    else
    {
        var checkbox1Value = "true";
        var checkbox1 = Array.prototype.slice.call(document.querySelectorAll('input[name="mulchoix1"]:checked'));

        for(var j=0;j<checkbox1.length;j++)
        {
            if(checkbox1[j].value === "false")
            {
                checkbox1Value = "false";
                break;
            }
        }

        if(checkbox1Value === "false")
        {
            incorrectanswers.push("3、应选ACD")
        }
        else if(checkbox1.length < 3)
        {
            partTrueOfCheckbox.push("3、应选ACD")
            score += 2;
        }
        else
        {
            score += 4;
        }
    }

    //4
    for(i=0;i<multiplechoixinput2.length;i++)
    {
        if(multiplechoixinput2[i].checked)
            break;
    }

    if(i === multiplechoixinput2.length)
    {
        nullchoice.push("4")
    }
    else
    {
        var checkbox2Value = "true";
        var checkbox2 = Array.prototype.slice.call(document.querySelectorAll('input[name="mulchoix2"]:checked'));
        for(var i=0;i<checkbox2.length;i++)
        {
            if(checkbox2[i].value === "false")
            {
                checkbox2Value = "false";
                break;
            }
        }

        if(checkbox2Value === "false")
        {
            incorrectanswers.push("4、应选AD")
        }
        else if(checkbox2.length < 2)
        {
            partTrueOfCheckbox.push("4、应选AD")
            score += 2;
        }
        else
        {
            score += 4;
        }
    }

    //多选题
    //判断题

    var TFqu = [];
    TFqu.push(document.querySelector('select[name="TFquestion1"]').value);
    TFqu.push(document.querySelector('select[name="TFquestion2"]').value);
    TFqu.push(document.querySelector('select[name="TFquestion3"]').value);
    TFqu.push(document.querySelector('select[name="TFquestion4"]').value);

    for(var i=1;i<=4;i++)
    {
        if(TFqu[i-1] === "none")
        {
            nullchoice.push("5(" + i +")");
        }
        else if(TFqu[i-1] === "false")
        {
            if(i === 1 || i === 2)
                incorrectanswers.push("5(" + i +")" + "、应选“正确”");
            else
                incorrectanswers.push("5(" + i +")" + "、应选“错误”");
        }
        else
        {
            score += 1;
        }
    }

    //输出

    if(!incorrectanswers.length&&!partTrueOfCheckbox.length&&!nullchoice.length)
    {
        message = ("您的回答全部正确！</br>");
    }
    else
    {
        if(incorrectanswers.length)
        {
            message += ("以下问题回答错误：");
        
            for(var i=0;i<incorrectanswers.length;i++)
            {
                message += incorrectanswers[i];
                if(i != incorrectanswers.length - 1)
                    message += "；";
                else
                    message += "。";
            }
            message += "</br>";
        }
        
        if(partTrueOfCheckbox.length)
        {
            message += ("以下问题部分选对：");
            for(var i=0;i<partTrueOfCheckbox.length;i++)
            {
                message += partTrueOfCheckbox[i];
                if(i != partTrueOfCheckbox.length - 1)
                    message += "；";
                else
                    message += "。";
            }
            message += "</br>"
        }

        if(nullchoice.length)
        {
            message += ("以下问题您未作答：")
            for(var i=0;i<nullchoice.length;i++)
            {
                message += nullchoice[i];
                if(i != nullchoice.length - 1)
                    message += "；";
                else
                    message += "。";
            }
            message += "</br>";
        }
    }

    message += "您的得分为：" + score + "分。</br>";

    message += "您的用时为：" + elaspedMinutes + "分钟" + elaspedSeconds + "秒。</br>";

    var timer = elaspedMinutes + "m" +elaspedSeconds + "s";
    var realtime = elaspedMinutes*60 + elaspedSeconds;
    var url= "answer.html?message111=" + encodeURIComponent(message) + "&score=" + encodeURIComponent(score) + "&timer=" + encodeURIComponent(timer) + "&realtime=" + encodeURIComponent(realtime);

    alert("提交成功！");

    window.open(url);
    window.location.reload();
}
