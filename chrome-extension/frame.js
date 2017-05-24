var elRepoName = document.querySelector('#js-repo-pjax-container > div.pagehead.repohead.instapaper_ignore.readability-menu.experiment-repo-nav > div.container.repohead-details-container > h1 > strong > a');
var repoName = elRepoName.getAttribute('href');

var elIssueId = document.querySelector('.gh-header-number');
var issueId = elIssueId.innerHTML.replace('#', '');

console.log(issueId);

// var url = 'http://productivity.gizra.com/' + repoName + '/' + issueId;
var url = "https://google.com";
document.querySelector('iframe').src = url;
