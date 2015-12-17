"use strict";angular.module("clientApp",["ngAnimate","ngCookies","ngSanitize","config","LocalStorageModule","ui.bootstrap","ui.router","angular-loading-bar","ui.calendar"]).config(["$stateProvider","$urlRouterProvider","$httpProvider","cfpLoadingBarProvider",function(a,b,c,d){var e=function(a,b,c){b.isAuthenticated()||c(function(){a.go("403")})};e.$inject=["$state","Auth","$timeout"],a.state("homepage",{url:"/",controller:"HomepageCtrl",resolve:{account:["Account",function(a){return a.get()}]}}).state("login",{title:"Login",url:"/login",templateUrl:"views/login.html",controller:"LoginCtrl"}).state("dashboard",{title:"Dashboard","abstract":!0,url:"",templateUrl:"views/dashboard/main.html",controller:"DashboardCtrl",onEnter:e,resolve:{account:["Account",function(a){return a.get()}]}}).state("dashboard.tracking-form",{title:"Tracking form",url:"/tracking/{username:string}/{year:int}/{month:int}/{day:string}/{id:string}",templateUrl:"views/dashboard/tracking-form.html",controller:"TrackingFormCtrl",onEnter:e,resolve:{projects:["$stateParams","Projects",function(a,b){return b.get(a.year,a.month)}],tracking:["$stateParams","Tracking",function(a,b){return b.get(a.year,a.month,a.username)}]}}).state("dashboard.tracking",{title:"Tracking",url:"/tracking/{year:int}/{month:int}",templateUrl:"views/dashboard/tracking.html",controller:"TrackingCtrl",onEnter:e}).state("dashboard.tracking-table",{title:"Tracking table",url:"/tracking-table/{year:int}/{month:int}",templateUrl:"views/dashboard/tracking-table.html",controller:"TrackingTableCtrl",onEnter:e,resolve:{tracking:["$stateParams","Tracking",function(a,b){return b.get(a.year,a.month)}],trackingProject:["$stateParams","TrackingProject",function(a,b){return b.get(a.year,a.month)}]}}).state("dashboard.tracking.track",{title:"Tracking table",url:"/tracking-table/{trackId:int}",templateUrl:"views/dashboard/tracking-table.html",controller:"TrackingCtrl",onEnter:e,resolve:{tracking:["$stateParams","Tracking",function(a,b){return b.get(a.year,a.month)}]}}).state("dashboard.account",{title:"My account",url:"/my-account",templateUrl:"views/dashboard/account/account.html",controller:"AccountCtrl",onEnter:e,resolve:{account:["Account",function(a){return a.get()}]}}).state("403",{title:"Forbidden",url:"/403",templateUrl:"views/403.html"}),b.otherwise("/"),c.interceptors.push(["$q","Auth","localStorageService",function(a,b,c){return{request:function(a){return a.url.match(/login-token/)||(a.headers={"access-token":c.get("access_token")}),a},response:function(a){return a.data.access_token&&c.set("access_token",a.data.access_token),a},responseError:function(c){return 401===c.status&&b.authFailed(),a.reject(c)}}}]),d.includeSpinner=!0,d.latencyThreshold=0}]).run(["$rootScope","$state","$stateParams","$log","Config",function(a,b,c,d,e){a.$state=b,a.$stateParams=c,a.debug=e.debugUiRouter,e.local||(e.backend=window.location.protocol+"//"+window.location.host+"/"),e.debugUiRouter&&(a.$on("$stateChangeStart",function(a,b,c,e,f){d.log("$stateChangeStart to "+b.to+"- fired when the transition begins. toState,toParams : \n",b,c)}),a.$on("$stateChangeError",function(a,b,c,e,f){d.log("$stateChangeError - fired when an error occurs during transition."),d.log(arguments)}),a.$on("$stateChangeSuccess",function(a,b,c,e,f){d.log("$stateChangeSuccess to "+b.name+"- fired once the state transition is complete.")}),a.$on("$viewContentLoaded",function(a){d.log("$viewContentLoaded - fired after dom rendered",a)}),a.$on("$stateNotFound",function(a,b,c,e){d.log("$stateNotFound "+b.to+"  - fired when a state cannot be found by its name."),d.log(b,c,e)}))}]),angular.module("clientApp").controller("HomepageCtrl",["$scope","$state","account",function(a,b,c){if(c){var d=new Date,e=d.getDate(),f=d.getMonth()+1,g=d.getFullYear();b.go("dashboard.tracking-form",{username:c.label,year:g,month:f,day:e,id:"new"})}else b.go("login")}]),angular.module("clientApp").controller("AccountCtrl",["$scope","account",function(a,b){a.account=b}]),angular.module("clientApp").controller("TrackingCtrl",["$scope","tracking","$stateParams","$log",function(a,b,c,d){function e(a){var b=d3.select(this).node().parentNode;d3.select(b).selectAll("circle").style("display","none"),d3.select(b).selectAll("text.value").style("display","block")}function f(a){var b=d3.select(this).node().parentNode;d3.select(b).select("text").style("display","none"),d3.select(b).select("text.value").style("display","block")}function g(a){var b=d3.select(this).node().parentNode;d3.select(b).selectAll("circle").style("display","block"),d3.select(b).selectAll("text.value").style("display","none")}function h(a){var b={};return angular.forEach(a,function(a){void 0==a.employee&&("regular"==a.type&&(a.employee=a.projectName),a.employee=a.type),void 0==b[a.employee]&&(b[a.employee]=[]),"day"==a.length.period&&(a.length.interval=8*parseInt(a.length.interval)),"regular"!=a.type&&(a.projectName=a.type,a.length.interval=8),void 0==b[a.employee]&&(b[a.employee]=[]),b[a.employee].push([a.day,a.length.interval,a.projectName,a.type])}),b}a.tracking=b,a.selectedTrack=null,a.year=c.year,a.month=c.month,a.eventSources=[];var i=1024,j=1,k=30,l=d3.scale.category20c(),m=d3.scale.linear().range([0,i]),n=d3.svg.axis().scale(m).orient("top"),o=d3.select(".tracking-data");m.domain([j,k]);var p=d3.scale.linear().domain([j,k]).range([0,i]);o.append("g").attr("class","x axis").attr("transform","translate(0,0)").call(n);var q=h(b),r=0;angular.forEach(q,function(a,b){var c=o.append("g").attr("class","journal"),d=c.selectAll("circle").data(a).enter().append("circle"),h=c.selectAll("text").data(a).enter().append("text"),j=c.selectAll("button").data(a).enter().append("text").on("mouseover",f).on("mouseout",g),k=d3.scale.linear().domain([0,d3.max(a,function(a){return a[1]})]).range([2,9]);d.attr("cx",function(a){return p(a[0])}).attr("cy",20*r+20).attr("r",function(a){return k(a[1])}).attr("class",function(a){return a[3]}).attr("data-toggle","tooltip").attr("data-placement","top").attr("title",function(a){return a[2]}),j.attr("y",20*r+25).attr("x",function(a){return p(a[0])-5}).attr("data-toggle","tooltip").attr("data-placement","top").style("display","none").text(function(a){return a[2]}).attr("title",function(a){return a[2]}),h.attr("y",20*r+25).attr("x",function(a){return p(a[0])-5}).attr("class","value").text(function(a){return a[1]}).style("fill",function(){return l(r)}).style("display","none"),c.append("text").attr("y",20*r+25).attr("x",i+20).attr("class","label").text(b).style("fill",function(){return l(r)}).on("mouseover",e).on("mouseout",g),r++}),$(function(){$('[data-toggle="tooltip"]').tooltip()});var s=function(b){a.selectedTrack=null,angular.forEach(a.tracking,function(c){c.id==b&&(a.selectedTrack=c)})};c.trackId&&s(c.trackId)}]),angular.module("clientApp").controller("TrackingFormCtrl",["$scope","$stateParams","$state","$log","projects","Tracking","tracking","Config","Preferences",function(a,b,c,d,e,f,g,h,i){a.tracking=g,h.debug&&console.log(g),a.calendar=angular.isDefined(i.getCalendarPreference())?JSON.parse(i.getCalendarPreference()):!1,a.calendarState=a.calendar?"Hide":"Show",a.toggleCalendar=function(){a.calendar=!a.calendar,i.setCalendarPreference(a.calendar),a.calendarState=a.calendar?"Hide":"Show"};var j=new Date(b.year,b.month,0).getDate();a.days=[];for(var k=1;j>=k;k++)a.days.push(k);var l=["January","February","March","April","May","June","July","August","September","October","November","December"];a.issueTypes=[{id:"dev",label:"Development"},{id:"qa",label:"QA"},{id:"management",label:"Management"},{id:"designer",label:"Designer"},{id:"non_billable",label:"None billable"},{id:"review",label:"Review"},{id:"support",label:"Support"}],a.vacationTypes={fullday:"Full day",halfday:"Half a day"},a.month=b.month,a.monthString=l[a.month-1],a.year=b.year,a.day=b.day,a.employee=b.username,a.nextMonth=a.month+1,a.nextYear=a.year,a.prevMonth=a.month-1,a.prevYear=a.year,12==a.month&&(a.nextMonth=1,a.nextYear=a.year+1),1==a.month&&(a.prevMonth=12,a.prevYear=a.year-1),a.creating=!1,a.projects=e,a.message="",a.messageClass="alert-success","new"==b.id||"undefined"==b.id?(a.title="What have you done on the "+b.day+"/"+b.month+"/"+b.year+" ?",a.data={},a.data.period="hour",a.data.type="regular",a.data.vacationType="fullday",a.data.length=0,a.data.issues=[{issue:0,label:"",type:"dev",time:""}],a.data.employee=b.username):(a.title="Your report for the "+b.day+"/"+b.month+"/"+b.year+" ?",angular.forEach(g[b.day],function(c){c.id==b.id&&(a.data=c)})),a.uiConfig={calendar:{height:400,editable:!1,day:a.day,month:a.month-1,year:a.year,header:{left:"",center:"",right:""}}},a.calendarEventTypes={regular:{className:"regular-event",events:[]},weekend:{className:"weekend-event",events:[]},miluim:{className:"miluim-event",events:[]},vacation:{className:"vacation-event",events:[]},sick:{className:"sick-event",events:[]},empty:{className:"empty-event",events:[]},convention:{className:"convention-event",events:[]},funday:{className:"funday-event",events:[]},special:{className:"special-event",events:[]},global:{className:"global-event",events:[]}},angular.forEach(g,function(b){angular.forEach(b,function(b){if(angular.isObject(b))if("regular"==b.type){var c=parseFloat(b.length),d=c>1?" Hours":" Hour";a.calendarEventTypes.regular.events.push({title:b.projectName+" - "+c+d,start:new Date(1e3*b.date),description:c,allDay:!0,type:b.type,url:"#/tracking/"+a.employee+"/"+a.year+"/"+a.month+"/"+b.day+"/"+b.id})}else a.calendarEventTypes[b.type].events.push({title:"global"==b.type?"Global day":b.projectName,start:new Date(a.year,a.month-1,b.day),allDay:!0,type:b.type,url:"empty"==b.type?"#/tracking/"+a.employee+"/"+a.year+"/"+a.month+"/"+b.day+"/new":"#/tracking/"+a.employee+"/"+a.year+"/"+a.month+"/"+b.day+"/"+b.id})})}),a.eventSources=[],angular.forEach(a.calendarEventTypes,function(a){this.push(a)},a.eventSources),a.save=function(d){if(a.creating=!0,"vacation"!=d.type&&delete d.vacationType,d.day=a.day,d.month=a.month,d.year=a.year,"regular"==d.type){var e=f.checkIssuesData(d.issues);if(d.length=e.totalHours,e.issuesErrors)return a.messageClass="alert-danger",a.message=e.issuesErrors,void(a.creating=!1)}h.debug&&console.log(d),f.save(d).then(function(d){if(a.creating=!1,d.error)return a.messageClass="alert-danger",void(a.message=d.title);if(a.messageClass="alert-success",a.message="Saved successfully.",0==d.data[0].status)return void c.go("dashboard.tracking-form",{username:b.username,year:b.year,month:b.month,day:b.day,id:"new"},{reload:!0});var e=d.data[0];e["new"]&&(g[e.day].push(e),b.id=e.id),c.go("dashboard.tracking-form",{username:e.employee,year:b.year,month:b.month,day:e.day,id:e.id},{reload:!0})})},a.owner=function(a){return a&&a.hasOwnProperty("id")&&b.username==a.employee},a.remove=function(c){return b.username!=c.employee?!1:(c.status=0,void a.save(c))},a.removeIssue=function(b){a.data.issues[b]&&(a.data.length-=a.data.issues[b].time,a.data.issues.splice(b,1))},a.addNewIssue=function(){a.data.issues.push({issue:0,label:"",type:"dev",time:""})},a.updateTotalHours=function(){var b=angular.element(".issue-time"),c=0;angular.forEach(b,function(a){c+=a.value?parseFloat(a.value):0}),a.data.length=c},a.changeProject=function(){a.data.issues=[],a.getPRs()},a.getPRs=function(){f.getGithubPRs(a.data.projectID,a.employee,a.day,a.month,a.year).success(function(b){for(var c in a.data.issues)a.data.issues[c].label||a.data.issues.splice(c,1);angular.forEach(b.data,function(b){for(var c in a.data.issues)if(a.data.issues[c].issue==b.id)return;a.data.issues.push({issue:b.id,label:"#"+b.issue+": "+b.label,type:"dev",time:""})}),a.data.issues.length||a.addNewIssue()})}}]),angular.module("clientApp").controller("TrackingTableCtrl",["$scope","tracking","trackingProject","$stateParams","$log","Config",function(a,b,c,d,e,f){for(var g=new Date(d.year,d.month,0).getDate(),h=[],i=1;g>=i;i++)h.push(i);a.trackingProject=c,a.employeeRows=b,a.year=d.year,a.month=d.month,a.nextMonth=a.month+1,a.nextYear=a.year,a.prevMonth=a.month-1,a.prevYear=a.year,12===a.month&&(a.nextMonth=1,a.nextYear=a.year+1),1===a.month&&(a.prevMonth=12,a.prevYear=a.year-1),a.days=h,f.debug&&console.log(a.employeeRows)}]),angular.module("clientApp").controller("LoginCtrl",["$scope","Auth","$state",function(a,b,c){a.loginButtonEnabled=!0,a.loginFailed=!1,a.login=function(d){a.loginButtonEnabled=!1,b.login(d).then(function(){c.go("homepage")},function(){a.loginButtonEnabled=!0,a.loginFailed=!0})}}]),angular.module("clientApp").controller("DashboardCtrl",["$scope","Auth","$state","account",function(a,b,c,d){var e=new Date;a.day=e.getDate(),a.month=e.getMonth()+1,a.year=e.getFullYear(),a.employee=d.label,a.logout=function(){b.logout(),c.go("login")}}]),angular.module("clientApp").service("Account",["$q","$http","$timeout","Config","$rootScope",function(a,b,c,d,e){function f(){var c=a.defer(),e=d.backend+"/api/me/";return b({method:"GET",url:e,transformResponse:g}).success(function(a){j(a[0]),c.resolve(a[0])}),c.promise}function g(a){return(a=angular.fromJson(a).data)?(angular.forEach(a[0].companies,function(b,c){a[0].companies[c].id=parseInt(b.id)}),a):void 0}var h={},i="ProductivityAccountChange";this.get=function(){return a.when(h.data||f())};var j=function(a){h={data:a,timestamp:new Date},c(function(){h={}},6e4),e.$broadcast(i)};e.$on("clearCache",function(){h={}})}]),angular.module("clientApp").service("Auth",["$injector","$rootScope","Utils","localStorageService","Config",function(a,b,c,d,e){this.login=function(b){return a.get("$http")({method:"GET",url:e.backend+"/api/login-token",headers:{Authorization:"Basic "+c.Base64.encode(b.username+":"+b.password)}})},this.logout=function(){d.remove("access_token"),b.$broadcast("clearCache"),a.get("$state").go("login")},this.isAuthenticated=function(){return!!d.get("access_token")},this.authFailed=function(){this.logout()}}]),angular.module("clientApp").service("Utils",function(){var a=this;this.Base64={_keyStr:"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",encode:function(b){var c,d,e,f,g,h,i,j="",k=0;for(b=a.Base64._utf8_encode(b);k<b.length;)c=b.charCodeAt(k++),d=b.charCodeAt(k++),e=b.charCodeAt(k++),f=c>>2,g=(3&c)<<4|d>>4,h=(15&d)<<2|e>>6,i=63&e,isNaN(d)?h=i=64:isNaN(e)&&(i=64),j=j+this._keyStr.charAt(f)+this._keyStr.charAt(g)+this._keyStr.charAt(h)+this._keyStr.charAt(i);return j},_utf8_encode:function(a){a=a.replace(/\r\n/g,"\n");for(var b="",c=0;c<a.length;c++){var d=a.charCodeAt(c);128>d?b+=String.fromCharCode(d):d>127&&2048>d?(b+=String.fromCharCode(d>>6|192),b+=String.fromCharCode(63&d|128)):(b+=String.fromCharCode(d>>12|224),b+=String.fromCharCode(d>>6&63|128),b+=String.fromCharCode(63&d|128))}return b}}}),angular.module("clientApp").service("Tracking",["$q","$http","$timeout","Config","$rootScope",function(a,b,c,d,e){var f={};this.get=function(b,c,d){return a.when(f.data||g(b,c,d))},this.save=function(c){var e=a.defer(),f=d.backend+"/api/tracking",g="POST";return c.id&&(g="PATCH",f+="/"+c.id),d.debug&&(f+="?XDEBUG_SESSION_START=13261"),b({method:g,url:f,data:c}).success(function(a){a.error=!1,e.resolve(a)}).error(function(a){a.error=!0,e.resolve(a)}),e.promise},this.getGithubPRs=function(a,c,e,f,g){return b({method:"GET",url:d.backend+"/api/github-prs",params:{"filter[project]":a,employee:c,year:g,month:f,day:e}})},this.checkIssuesData=function(a){var b={issuesErrors:"",totalHours:0},c=["label","type","time"];return a.length?(angular.forEach(a,function(a){angular.forEach(c,function(c){return a[c]?void 0:(b.issuesErrors+="Please fill the "+c+" in all the issues. ",!1)}),b.totalHours+=parseFloat(a.time)}),b):(b.issuesErrors="At least one issue should be added.",b)};var g=function(c,e,f){var g=a.defer(),h=d.backend+"/api/tracking?year="+c+"&month="+e;return void 0!==f&&(h+="&employee="+f),d.debug&&(h+="&XDEBUG_SESSION_START=13261"),b({method:"GET",url:h}).success(function(a){g.resolve(a.data)}),g.promise};e.$on("clearCache",function(){f={}})}]),angular.module("clientApp").service("TrackingProject",["$q","$http","$timeout","Config","$rootScope",function(a,b,c,d,e){var f={},g="ProductivityTrackingProjectChange";this.get=function(b,c){return a.when(i(b,c)||h(b,c))};var h=function(c,e){var f=a.defer(),g=d.backend+"/api/tracking-project?year="+c+"&month="+e;return console.log(g),d.debug&&(g+="&XDEBUG_SESSION_START=14241"),b({method:"GET",url:g}).success(function(a){j(a.data,c,e),f.resolve(a.data)}),f.promise},i=function(a,b){return void 0!=f[a+"_"+b]?f[a+"_"+b].data:!1},j=function(a,b,d){f[b+"_"+d]={data:a,timestamp:new Date},c(function(){f={}},9e5),e.$broadcast(g)};e.$on("clearCache",function(){f={}})}]),angular.module("clientApp").service("Preferences",["localStorageService",function(a){this.getCalendarPreference=function(){return a.get("calendar")},this.setCalendarPreference=function(b){a.set("calendar",b)}}]),angular.module("clientApp").service("Projects",["$q","$http","$timeout","Config","$rootScope",function(a,b,c,d,e){var f={},g="ProductivityProjectsChange";this.get=function(b,c){return a.when(f.data||h(b,c))},this.save=function(c){var e=a.defer(),f=d.backend+"/api/projects";return b({method:"POST",url:f,data:c}).success(function(a){}),e.promise};var h=function(c,e){var f=a.defer(),g={sort:"label",year:c,month:e},h=d.backend+"/api/projects";return b({method:"GET",url:h,params:g}).success(function(a){i(a.data),f.resolve(a.data)}),f.promise},i=function(a){f={data:a,timestamp:new Date},c(function(){f={}},6e4),e.$broadcast(g)};e.$on("clearCache",function(){f={}})}]),angular.module("clientApp").directive("loadingBarText",function(){return{restrict:"EA",template:"",controller:["$scope",function(a){function b(b){a.isLoading=b}a.isLoading=!1,a.$on("cfpLoadingBar:started",function(){b(!0)}),a.$on("cfpLoadingBar:completed",function(){b(!1)})}],scope:{}}});