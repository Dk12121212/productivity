<tr id="attr<?php print $row_number; ?>" mlid="<?php print $tracking['mlid'] ? $tracking['mlid'] : 'new'; ?>" <?php print $tracking['mlid'] ? "" : 'class="new"';?> delete="0">
  <td class="save-mark">
    <?php print $tracking['nodelink']; ?>
    <i class="fa fa-check text-primary" aria-hidden="true" style="display: none;"></i>
  </td>
  <td width="16%">
    <select  name="project" class="form-control disable-after-save" value="<?php print $tracking['project_nid']; ?>" <?php print $tracking['disabled']; ?>>
      <?php foreach ($projects as $key => $project): ?>
        <option value="<?php print $key; ?>" <?php print ($key==$tracking['project_nid']) ? 'selected="selected"' : ''; ?>><?php print $project; ?></option>
      <?php endforeach; ?>
    </select>
  </td>
  <td width="14%">
    <input value="<?php print $tracking['repo']; ?>" type="text" name='repo' placeholder='Gizra/some-repo' class="form-control disable-after-save" <?php print $tracking['disabled']; ?>/>
  </td>
  <td width="9%">
    <?php if (isset($tracking['issue_href'])): ?>
      <a href="<?php print $tracking['issue_href']; ?>" target="_blank">
    <?php endif; ?>
    <input value="<?php print $tracking['issue']; ?>" type="number" name='issue' placeholder='#' class="form-control disable-after-save" <?php print $tracking['disabled']; ?>/>
    <?php if (isset($tracking['issue_href'])): ?>
      </a>
    <?php endif; ?>
  </td>
  <td width="12%">
    <form class="form-inline">
      <div class="form-group">
        <label class="sr-only" for="exampleInputAmount">Amount (in dollars)</label>
        <div class="input-group">
          <?php if (isset($tracking['pr_href'])): ?>
            <a href="<?php print $tracking['pr_href']; ?>" target="_blank" class="input-group-addon"><i class="fa fa-external-link" aria-hidden="true"></i></a>
          <?php endif; ?>
          <input value="<?php print $tracking['pr']; ?>" type="number" name='pr' placeholder='#' class="form-control"/>
        </div>
      </div>
    </form>
  </td>
  <td width="28%">
    <input value="<?php print check_plain($tracking['title']); ?>" type="text" name='title' placeholder='Description - Leave empty to get title of PR from GH ' class="form-control"/>
  </td>
  <td width="10%">
    <select id="selectType" name="type" class="form-control" value="<?php print $tracking['type']; ?>">
      <?php foreach ($types as $key => $type): ?>
        <option value="<?php print $key; ?>" <?php print ($key==$tracking['type']) ? 'selected="selected"' : ''; ?>><?php print $type; ?></option>
      <?php endforeach; ?>
    </select>
  </td>
  <td width="8%">
  <input value="<?php print $tracking['length']; ?>" name="issue-time" type="number" step="0.10" min="0" placeholder="4" class="form-control input-md issue-time">
  </td>
  <td width="3%">
    <button class="btn btn-danger deleteRow" row="attr<?php print $row_number; ?>" type="button" title="Delete Row" data-placement="bottom">
      <i class="fa fa-trash-o"></i>
    </button>
  </td>
</tr>