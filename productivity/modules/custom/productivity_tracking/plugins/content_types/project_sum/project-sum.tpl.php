<div id="project-sum">
  <div class="row clearfix">
    <div class="col-lg-6">
      <h3><span>Monthly project breakdown</span></h3>
      <ul class="list-group">
        <?php foreach($tracking['sum']['projects'] as $project_nid => $data): ?>
          <li class="list-group-item">
            <span class="badge badge-primary"><?php print $data['sum']; ?></span>
            <?php print $data['name']; ?>
          </li>
        <?php endforeach; ?>
        <li class="list-group-item">
          <span class="badge badge-danger"><?php print $tracking['sum']['month']; ?></span>
          Monthly total
        </li>
      </ul>
    </div>
  </div>
</div>