var loc = document.getElementById("myLocation");

function findLoca() {
    if (navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(showYourLocation);
    } else {
        loc.innerHTML = "이 문장은 사용자의 웹 브라우저가 Geolocation API를 지원하지 않을 때 나타납니다!";
    }
}

function showYourLocation(position) {
    loc.innerHTML = "현재 사용자는 위도 " + position.coords.latitude + ", 경도 " + position.coords.longitude + "에 위치하고 있습니다.";
}

//모나리자 버튼누르면 움직이기 

function B() {
    var paper = document.getElementById("CanMona");
    var context = paper.getContext("2d");
    var srcImg = document.getElementById("monalisa");
    context.drawImage(srcImg, 0, 0); //왼쪽위 포인터의 위치 (드래그 시작)
}


//모나리자 드래그앤 드롭 

/*
let distX;
let distY;
let posX;
let posY;

function dragstart(ev) {
    posX = ev.pageX;
    posY = ev.pageY;
    distX = ev.srcElement.offsetLeft - posX;
    distY = ev.srcElement.offsetTop - posY;
}

function dragover(ev) {
    ev.stopPropagation();
    ev.preventDefault();
}

function drop(ev) {
    ev.stopPropagation();
    ev.preventDefault();
    posX = ev.pageX;
    posY = ev.pageY;
    console.log(posX, posY, distX, distY);
    $('#mydiv').css('margin-left', posX + distX + 'px')
        .css('margin-top', posY + distY + 'px');
}*/


function dragEnter(ev) { //누울 자리 보고 발뻗는다고 들어올 수 있을때 시작한다: 움직인다. 
    ev.stopPropagation();
    ev.preventDefault(); // 내 자리로 들어올 수  있게끔 한다. 
}

function drag(ev) {
    ev.dataTransfer.setData("text", ev.target.id);
}

function drop(ev) {
    ev.stopPropagation();
    ev.preventDefault();
    var data = ev.dataTransfer.getData("text");
    ev.target.appendChild(document.getElementById(data));
}