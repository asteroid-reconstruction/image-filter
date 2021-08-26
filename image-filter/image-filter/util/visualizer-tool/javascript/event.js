window.document.addEventListener('DOMContentLoaded', () => {

    var clickState = false;

    document.getElementById('nav-tool-statistics').addEventListener('click', (event) => {
        clickState = !clickState;
        document.getElementById('nav-tool-statistics').style.backgroundColor = clickState ? 'moccasin' : 'rgb(230,230,230)';
    })
})