$(function () {

    $('#toLogin').on('click', function () {
        document.getElementById('registerWindow').hidden = 'hidden';
        document.getElementById('loginWindow').removeAttribute('hidden');
    });

    $('#toRegister').click(function $(){
        document.getElementById('loginWindow').hidden = 'hidden';
        document.getElementById('registerWindow').removeAttribute('hidden');
    });

    $('#submitRegister').click(function $(){
        let email = document.getElementById('registerEmail').value;
        let password = document.getElementById('registerPassword').value;
        let passwordRepeat = document.getElementById('registerPasswordRepeat').value;
        if(
            email == '' ||
            password == '' ||
            password != passwordRepeat
        ){
            confirm('error');
        }
        else{
            localStorage['email'] = email;
            localStorage['password'] = password;
            window.location.href = '/BikeStore/html/index.html';
        }
    });

    $('#submitLogin').click(function $(){
        let email = document.getElementById('loginEmail').value;
        let password = document.getElementById('loginPassword').value;
        if(
            email == '' ||
            password == ''
        ){
            confirm('error');
        }
        else{
            localStorage['email'] = email;
            localStorage['password'] = password;
            window.location.href = '/BikeStore/html/index.html';
        }
    });


});