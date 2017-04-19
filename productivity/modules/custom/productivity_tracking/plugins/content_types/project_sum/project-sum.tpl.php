<div id="project-sum">
  <ul class="list-group">
    <?php foreach($tracking['sum']['projects'] as $project_key => $data): ?>
      <li class="list-group-item">
        <span class="badge badge-primary"><?php print $data['sum']; ?></span>
        <a href="<?php print url('node/' . $data['nid']); ?>"><?php print $data['name']; ?></a>
      </li>
    <?php endforeach; ?>
    <li class="list-group-item">
      <span class="badge badge-danger"><?php print $tracking['sum']['month']; ?></span>
      Monthly total
    </li>
  </ul>
</div>