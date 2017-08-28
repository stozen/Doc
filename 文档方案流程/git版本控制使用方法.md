# git版本控制使用方法


>git与svn区别：最主要区别就是git是分布式的管理系统，即使没有网络，也可以在本地进行代码的提交和管理

###准备工作

**环境**

要使用git版本控制，首先本地当然要有配置好的相关环境，一般安装了Android studio的都自动集成好了，如果没有也可以网上查找相关内容去搭建git环境。如果是Mac电脑的话则自动集成了git，只要确保尽量是新版本就行

**密钥**

一般git远程代码管理使用ssh密钥作为身份认证方式，因此需要进行相关的配置。本地生成ssh key的命令是：
`ssh-keygen -t rsa -C “eric@everzones.com”`
为了符合运维团队制定的git服务器使用规范，后边的邮箱就使用工作邮箱就行了。
在终端里输入命令后一般连按三个回车就可以，会在.ssh目录下生成相应的私钥和公钥，名字分别为`id_rsa`和`id_rsa.pub`，这个是默认名字，如果本地有多个git账号则需要创建config文件来管理，基本格式如下：

```
#evz
Host 192.168.1.89
HostName 192.168.1.89
User eric@everzones.com
PreferredAuthentications publickey
IdentityFile ~/.ssh/id_rsa_evz

#github
Host github.com
HostName github.com
User qyzhaojinxi@163.com
PreferredAuthentications publickey
IdentityFile ~/.ssh/id_rsa_github
```
同样是在.ssh目录下。

一般除了邮箱以外，还需要配置一下git使用过程中的用户名，分别如下：

```
git config --global user.name "eric"
git config --global user.email "eric@everzones.com"
```
这种方式是给整个电脑全局设置了同样的邮箱和用户名。如果想在单独某个项目下设置不同的，则需要使用终端进入到仓库目录下，执行这两个命令，修改邮箱和用户名。

**测试**

密钥设置完之后则需要进行一次测试，看是否密钥没有问题，终端输入如下命令：
`ssh -T git@192.168.1.89`
结果返回：
`Enter passphrase for key '/Users/melonzone/.ssh/id_rsa_evz':`
按照提示输入密码，没有密码的会跳过，最终返回下边的语句，表明测试成功，当前git密钥已经配置好了。
`hello Eric, this is git@www running gitolite3 v3.6.7-2-g7aecda4 on git 2.5.0`

###git仓库

目前运维团队帮我们创建了三个仓库，分别是`mobile_caller_tony`，`mobile_aio_will`，`mobile_test`。其中mobile_test为给我们练手的测试仓库。git服务器的访问地址为`git@192.168.1.89`。

**克隆**

首先我们以测试仓库为例子，演示一下如何开始使用git做版本管理。

目前mobile_test的仓库在远程服务器上是已经存在的，可能为空，也可能有东西，具体情况我们需要先将该仓库clone下来才能知晓。命令如下：

`git clone git@192.168.1.89:mobile_test`

有密码则输入密码，然后等待任务完成，很快就会发现在目录下出现了下载好的仓库`mobile_test`。执行该命令之前，可以使用终端进入想将该仓库放入的目录，然后执行命令，仓库就会克隆到该目录。

**基本操作**

`git status`:

用来查看当前仓库的基本状态，需要执行add命令添加到缓存区，还是需要使用`commit`命令提交，或者需要使用`push`命令推送代码到远程仓库等等。

`git log`：

用来打印近期的提交记录，使用`git log --graph` 命令则可看到简单地提交记录图谱，当然还有其他自定义的操作，感兴趣的话可以自己研究。

`git add`:

该命令是将更改的代码添加到缓存区，后边跟具体的文件路径，例如`git add test.txt`则是将该文件添加到缓存区。也可以直接使用`git add -A`则是添加当前路径下的所有改变到缓存区。

`git commit`:

提交代码到本地仓库，例如：

`git commit -m "测试提交"`

后边的文本信息则是提交内容的描述，例如做了什么修改等等。

`git push origin master`:

该命令就是将近期进行的所有commit提交，推动到远程代码仓库里去，相当于同步本地当前分支代码到远程仓库主分支。

`git pull`

如果该项目是多个人进行协作，其他成员也可能对远程代码做了修改或者提交。为了防止项目冲突导致提交失败，则需要先把远程代码拉取到本地与本地仓库当前分支作对比之后再push提交。如果远程端有修改则该命令会自动将拉取的代码和本地仓库代码合并，合并之后没有问题才可以push。

`git remote -v`

查看远程仓库地址

`git branch`和`git branch -v`

查看本地分支和远程分支

`git tag v1.0 -m ""`
给当前分支打标签作为版本，后边`-m`为描述，可以不添加

`git push origin v1.0`
由于标签不会随着代码提交而被推送到远程，需要手动执行该命令

`git tag -d v1.0`
删除本地标签



**恢复操作**

有时候难免将错误的代码进行了保存，或者甚至提交了，如果不清楚做了哪些修改的话，就会恢复起来很麻烦，而git则很好的解决了这个问题

主要依靠`git reset`和`git checkout`这两个命令，下边根据具体情况处理，对于文件test.txt:

* 修改后未add（还没有添加到暂存区），需要撤销之前的修改时：
  `git checkout --test.txt`或者手动对代码进行恢复。
  
  工作区：clean  暂存区：clean
  
* 修改后add了（未commit），又再次进行了其他修改，需要撤销第二次修改时：
  `git checkout --test.txt`（将暂存区代码恢复到工作区，第二次修改被丢弃了）
  
  暂存区：有第一次修改的代码add了，需要commit
  
* 修改后add了（未commit），需要撤销修改时：
  `git reset HEAD test.txt`（将暂存区代码修改删除）
  
  此时工作区的修改还未撤销（目前是恢复到add前，也就是第一种情况）
   `git checkout --test.txt`(撤销工作区的修改)
   
* 修改后add并commit了，需要撤销修改时：

   `git reset --hard HEAD^`(版本回退到上一次提交)
   
   或者
   
   `git rest --hard id`(该`id为`每次`commit`后生成的id，该命令指定回退到某次提交,id可通过`git log`获得)
   
* 最后还有个终极大招，如果本地已经做了很多次commit了，想恢复到和远程一样时：

 `git fetch --all`
 `git reset --hard origin/master`
 `git pull`
 
**分支**

一般为了防止一些修改对主项目有影响，或者要临时有一个功能的需求或者bug修复等等，往往都需要创建一个新的分支。而在该分支做的任何操作，对主分支都没有任何影响。

`git branch dev`
 创建了一个名叫dev的分支
 
 `git checkout dev`
 
 切换到dev分支
 
 `git checkout -b dev`
 
 创建并且换到dev分支
 
 `git branch -d dev`
 
 在其他分支时执行，删除dev分支
 
 `git merge dev`
 
 在master分支执行该命令，意思是将dev分支合并到master分支
 ***注意：在使用该命令时最好带上`--no-ff`，则可以保存dev分支的提交记录***
 
 `git rebase master`
 
 假如当前处于dev分支，master分支有更新，则可以使用rebase命令，将master分支的修改更新到当前dev，分支，效果和merge类似。不建议master分支使用rebase命令，dev分支最好经常rebase，获取master最新修改，防止后期合并时候和master有太多冲突。
 
 
###协作workflow

* 远程仓库主要有两个分支，master分支和dev分支,本地分支有master分支，dev分支，同时根据需要也可以创建其他分支,例如feature或者bug等自定义分支

* 平时操作都在本地dev分支或其他分支上操作，最终每天将本地dev分支最新代码提交到远程dev分支

* 每次提交dev分支前一定要先将远程dev分支最新代码使用pull命令更新到本地dev分支，防止推送到远程仓库时本地代码不是最新的，出现冲突

* 每天开始工作时同样需要将远程dev分支代码pull更新到本地dev分支，适用于多人协作，更新本地dev为最新代码

* 某个版本完成后，项目主程将本地dev分支最新代码合并到本地master分支，检查测试无问题后，将本地master分支推送到远程master分支

***注意：平时代码提交时任何人都不得对远程master分支做任何操作***
 
 
 




