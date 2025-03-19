$(function () {

    $(document).ready(function () {
        let email = localStorage.getItem("email");
        if (email !== null) {
            var toHide = document.getElementsByClassName('not-logined');

            for (var i = 0; i < toHide.length; i++) {
                toHide[i].style.display = 'none';
            }
        }
        else {
            var toHide = document.getElementsByClassName('logined');

            for (var i = 0; i < toHide.length; i++) {
                toHide[i].style.display = 'none';
            }
        }
    });

    $('#btSearch').on('click', function () {
        let search = document.getElementById('search').value;
        localStorage['search'] = search;
        // confirm(search);
        window.location.href = '/BikeStore/html/auth.html';
    });

});