var url = window.location.href
  .replace('/issues', '')
  .replace('https://github.com', '');

// @todo: This will need to be HTTPS
 var url = 'https://productivity.gizra.com/' + repoName + '/' + issueId;
document.querySelector('iframe').src = url;
