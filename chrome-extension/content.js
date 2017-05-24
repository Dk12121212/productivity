var elRepoName = document.querySelector('#js-repo-pjax-container > div.pagehead.repohead.instapaper_ignore.readability-menu.experiment-repo-nav > div.container.repohead-details-container > h1 > strong > a');
var repoName = elRepoName.getAttribute('href');

var elIssueId = document.querySelector('.gh-header-number');
var issueId = elIssueId.innerHTML.replace('#', '');

console.log(repoName);
console.log(issueId);

var el = document.querySelector('.gh-header-meta');
el.insertAdjacentHTML('afterend', '<iframe src="http://productivity.gizra.com/' + repoName + '/' + issueId + '" width="100%" height="100px"></iframe>');
